/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include "include/TcpClient.hpp"
#include "include/constants.hpp"

void TcpClient::handle_connect(const boost::system::error_code& error) {
    if (!error) {
        _event_callback(NetEventType::CONNECTED, "");
        connected = true;
        read_header();
    } else {
        throw std::exception();
    }
}

void TcpClient::read_header() {
    boost::asio::async_read(
        _socket,
        boost::asio::buffer(read_packet_.get_data(), Packet::header_length),
        std::bind(
            &TcpClient::handle_read_header,
            this,
            std::placeholders::_1  // error
        )
    );
}

void TcpClient::read_body() {
    boost::asio::async_read(
        _socket,
        boost::asio::buffer(read_packet_.get_body(), read_packet_.get_body_length()),
        std::bind(
            &TcpClient::handle_read_body,
            this,
            std::placeholders::_1  // error
        )
    );
}

void TcpClient::handle_read_header(const boost::system::error_code& error) {
    if (!error && read_packet_.decode_header()) {
        read_body();
    } else {
        do_close();
    }
}

void TcpClient::handle_read_body(const boost::system::error_code& error) {
    if (!error) {
        _event_callback(NetEventType::RECEIVED, read_packet_.get_as_string());
        read_header();
    } else {
        do_close();
    }
}

void TcpClient::write_next() {
    boost::asio::async_write(_socket,
        boost::asio::buffer(write_packets_.front().get_data(), write_packets_.front().size()),
        std::bind(
            &TcpClient::handle_write,
            this,
            std::placeholders::_1  // error
        )
    );
}

void TcpClient::do_write(Packet packet) {
    bool write_in_progress = !write_packets_.empty();
    write_packets_.push_back(packet);
    if (!write_in_progress) {
        write_next();
    }
}

void TcpClient::handle_write(const boost::system::error_code& error) {
    if (!error) {
        write_packets_.pop_front();
        if (!write_packets_.empty()) {
            write_next();
        }
    } else {
        do_close();
    }
}

void TcpClient::do_close() {
    if (is_connected()) {
        _event_callback(NetEventType::DISCONNECTED, "");
        connected = false;
        _socket.close();
    }
}

TcpClient::TcpClient(const std::string &host, const std::string &port, net_client_event_callback event_callback):
        host(host),
        port(port),
        _event_callback(event_callback),
        _socket(_io_service) {
    boost::asio::ip::tcp::resolver resolver(_io_service);
    boost::asio::ip::tcp::resolver::query query(host.c_str(), port.c_str());
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    boost::asio::async_connect(
        _socket,
        endpoint_iterator,
        std::bind(
            &TcpClient::handle_connect,
            this,
            std::placeholders::_1  // error
        )
    );
}

void TcpClient::connect() {
    _io_service.run();
}

bool TcpClient::is_connected() {
    return !_io_service.stopped() && connected;
}

void TcpClient::send(const std::string &data) {
    Packet packet(data);
    packet.encode_header();

    _io_service.post(std::bind(&TcpClient::do_write, this, packet));
}

void TcpClient::close() {
    _io_service.post(std::bind(&TcpClient::do_close, this));
}
