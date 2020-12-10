#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <set>

#include <thread>

#include <boost/asio.hpp>

#include "include/Packet.hpp"
#include "include/TcpServer.hpp"

void Room::join(PSession player) {
    _players.insert(player);
}

void Room::leave(PSession player) {
    _players.erase(player);
}

int Room::get_players_amount() {
    return _players.size();
}

void Room::send_all(const Packet& packet) {
    std::for_each(
        _players.begin(),
        _players.end(),
        [packet](auto player) {
            player->send(packet);
        }
    );
}

void PlayerSession::read_next_msg() {
    boost::asio::async_read(
        _socket,
        boost::asio::buffer(_read_msg.get_data(), Packet::header_length),
        std::bind(
            &PlayerSession::handle_read_header,
            shared_from_this(),
            std::placeholders::_1  // error
        )
    );
}

void PlayerSession::write_next_msg(const Packet msg) {
    boost::asio::async_write(
        _socket,
        boost::asio::buffer(msg.get_data(), msg.size()),
        std::bind(
            &PlayerSession::handle_write,
            shared_from_this(),
            std::placeholders::_1  // error
        )
    );
}

void PlayerSession::start() {
    _room.join(shared_from_this());
    read_next_msg();
}

void PlayerSession::send(const Packet& msg) {
    bool write_in_progress = !_write_msgs.empty();
    _write_msgs.push_back(msg);
    if (!write_in_progress) {
        write_next_msg(msg);
    }
}

void PlayerSession::handle_read_header(const boost::system::error_code& error) {
    if (!error && _read_msg.decode_header()) {
        boost::asio::async_read(
            _socket,
            boost::asio::buffer(_read_msg.get_body(), _read_msg.get_body_length()),
            std::bind(
                &PlayerSession::handle_read_body,
                shared_from_this(),
                std::placeholders::_1  //error
            )
        );
    } else {
        _room.leave(shared_from_this());
    }
}

void PlayerSession::handle_read_body(const boost::system::error_code& error) {
    if (!error) {
        std::cout << "Received: " << _read_msg.get_as_string() << std::endl;
        read_next_msg();
    } else {
        _room.leave(shared_from_this());
    }
}

void PlayerSession::handle_write(const boost::system::error_code& error) {
    if (!error) {
        _write_msgs.pop_front();
        if (!_write_msgs.empty()) {
            write_next_msg(_write_msgs.front());
        }
    } else {
        _room.leave(shared_from_this());
    }
}

// ------

TcpServer::TcpServer(int port): _acceptor(
        _io_service,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    start_accept();
}

void TcpServer::start_accept() {
    // accepts new connection
    std::shared_ptr<PlayerSession> new_session(
        new PlayerSession(_free_uid, _io_service, _room)
    );
    _free_uid++;
    _acceptor.async_accept(
        new_session->socket(),
        std::bind(
            &TcpServer::handle_accept,
            this,
            new_session,
            std::placeholders::_1  // error
        )
    );
}

void TcpServer::handle_accept(std::shared_ptr<PlayerSession> session, const boost::system::error_code& error) {
    std::cout << "Player " << session->getUid() << " connected" << std::endl;
    if (!error) {
        session->start();
    }
    start_accept();
}

void TcpServer::send_all(std::string data) {
    Packet packet(data);
    _room.send_all(packet);
}
