#ifndef SRC_TCPSERVER_HPP_
#define SRC_TCPSERVER_HPP_

#include <algorithm>
#include <deque>
#include <list>
#include <set>

#include <thread>

#include <boost/asio.hpp>

#include "Packet.hpp"

class Session {
 public:
    virtual ~Session() {}
    virtual void send(const Packet& msg) = 0;
};

typedef std::shared_ptr<Session> PSession;

class Room {
 private:
    std::set<PSession> _players;
 public:
    void join(PSession player);
    void leave(PSession player);
    void send_all(const Packet& msg);
};

class PlayerSession: public Session,
                     public std::enable_shared_from_this<PlayerSession> {
private:
    unsigned _uid;
    boost::asio::ip::tcp::socket _socket;
    Room& _room;
    Packet _read_msg;
    std::deque<Packet> _write_msgs;
public:
    PlayerSession(unsigned uid, boost::asio::io_service& io_service, Room& room)
    : _uid(uid),
      _socket(io_service),
      _room(room) {}

    unsigned getUid() const {
        return _uid;
    }
    boost::asio::ip::tcp::socket& socket() {
        return _socket;
    }

    void start();
    void read_next_msg();
    void write_next_msg(const Packet msg);
    void send(const Packet& msg);

    void handle_read_header(const boost::system::error_code& error);
    void handle_read_body(const boost::system::error_code& error);
    void handle_write(const boost::system::error_code& error);
};

class TcpServer {
 private:
    unsigned _free_uid = 1;
    std::set<PSession> _players;
    boost::asio::io_service _io_service;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> _p_acceptor;
    Room _room;
 public:
    TcpServer(int port);

    void start() {
        _io_service.run();
    }
    void stop() {
        _io_service.stop();
    }
    bool is_running() {
        return !_io_service.stopped();
    }
    void start_accept();
    void handle_accept(std::shared_ptr<PlayerSession> session, const boost::system::error_code& error);
    void send_all(std::string data);
};

#endif
