#ifndef SRC_TCPSERVER_HPP_
#define SRC_TCPSERVER_HPP_

#include <algorithm>
#include <deque>
#include <list>
#include <set>

#include <thread>

#include <boost/asio.hpp>

#include "include/Packet.hpp"
#include "include/common.hpp"

typedef std::function<void(NetEventType::NetEventType, unsigned, std::string)> net_server_event_callback;

class Session {
 public:
    virtual ~Session() {}
    virtual void send(const Packet& msg) = 0;
    virtual unsigned getUid() const = 0;
};

typedef std::shared_ptr<Session> PSession;

class Room {
 private:
    std::set<PSession> _players;
    net_server_event_callback &_event_callback;
 public:
    Room(net_server_event_callback &event_callback): _event_callback(event_callback) {}

    void join(PSession player);
    void leave(PSession player);
    int get_players_amount();
    void send_all(const Packet& msg);
};

class PlayerSession: public Session,
                     public std::enable_shared_from_this<PlayerSession> {
private:
    unsigned _uid;
    boost::asio::ip::tcp::socket _socket;
    Room& _room;
    net_server_event_callback &_event_callback;
    Packet _read_msg;
    std::deque<Packet> _write_msgs;
public:
    PlayerSession(unsigned uid, boost::asio::io_service& io_service, Room& room, net_server_event_callback &event_callback)
    : _uid(uid),
      _socket(io_service),
      _room(room),
      _event_callback(event_callback) {}

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
    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::resolver::iterator _endpoint_iterator;
    boost::asio::ip::tcp::acceptor _acceptor;
    net_server_event_callback _event_callback;
    Room _room;
 public:
    TcpServer(int port, net_server_event_callback event_callback);

    void start() {
        _io_service.run();
    }
    void stop() {
        _io_service.stop();
    }
    bool is_running() {
        return !_io_service.stopped();
    }
    int get_players_amount() {
        return _room.get_players_amount();
    }
    void start_accept();
    void handle_accept(std::shared_ptr<PlayerSession> session, const boost::system::error_code& error);
    void send_all(std::string data);
};

#endif
