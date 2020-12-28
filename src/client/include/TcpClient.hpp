/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/
#ifndef SRC_CLIENT_TCPCLIENT_HPP_
#define SRC_CLIENT_TCPCLIENT_HPP_

#include <iostream>

#include <cstdlib>
#include <deque>
#include <boost/asio.hpp>

#include "include/common.hpp"
#include "include/Packet.hpp"

typedef std::function<void(NetEventType::NetEventType, std::string)> net_client_event_callback;
typedef std::deque<Packet> Packet_queue;

class TcpClient {
 private:
   std::string host;
   std::string port;
   net_client_event_callback _event_callback;
   bool connected = false;

   boost::asio::io_service _io_service;
   boost::asio::ip::tcp::socket _socket;
   Packet read_packet_;
   Packet_queue write_packets_;

   void read_header();
   void read_body();
   void write_next();

   void handle_connect(const boost::system::error_code&);
   void handle_read_header(const boost::system::error_code&);
   void handle_read_body(const boost::system::error_code&);
   void handle_write(const boost::system::error_code&r);
   void do_write(Packet);

   void do_close();

 public:
    TcpClient(const std::string&, const std::string&, net_client_event_callback);
    void connect();
    bool is_connected();
    void send(const std::string&);
    void close();
};

#endif  // SRC_CLIENT_TCPCLIENT_HPP_
