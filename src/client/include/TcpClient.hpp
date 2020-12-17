/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/
#ifndef SRC_CLIENT_TCPCLIENT_HPP_
#define SRC_CLIENT_TCPCLIENT_HPP_

#include <iostream>

#include <cstdlib>
#include <deque>
#include <boost/asio.hpp>
#include "include/Packet.hpp"

typedef std::deque<Packet> Packet_queue;

class TcpClient {
 private:
   boost::asio::io_service *io_service_;
   boost::asio::ip::tcp::socket socket_;
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
    TcpClient(boost::asio::io_service*, boost::asio::ip::tcp::resolver::iterator);
    void send(const std::string&);
    void close();
};

#endif
