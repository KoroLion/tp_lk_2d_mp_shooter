#include "include/TcpClient.hpp"

void TcpClient::handle_connect(const boost::system::error_code& error) {
    if (!error) {
        std::cout << "CONNECTED!" << std::endl;
        read_header();
    } else {
        std::cout << "ERROR!" << std::endl;
    }
}

void TcpClient::read_header() {
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(read_packet_.get_data(), Packet::header_length),
        std::bind(
            &TcpClient::handle_read_header,
            this,
            std::placeholders::_1    // error
        )
    );
}

void TcpClient::read_body() {
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(read_packet_.get_body(), read_packet_.get_body_length()),
        std::bind(
            &TcpClient::handle_read_body,
            this,
            std::placeholders::_1    // error
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
        std::cout << read_packet_.get_as_string() << std::endl;
        read_header();
    } else {
        do_close();
    }
}

void TcpClient::write_next() {
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_packets_.front().get_data(), write_packets_.front().size()),
        std::bind(
            &TcpClient::handle_write,
            this,
            std::placeholders::_1    // error
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
    std::cout << "DISCONNECTED" << std::endl;
    socket_.close();
}

TcpClient::TcpClient(boost::asio::io_service *io_service, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    : io_service_(io_service),
      socket_(*io_service) {

    boost::asio::async_connect(
        socket_,
        endpoint_iterator,
        std::bind(
            &TcpClient::handle_connect,
            this,
            std::placeholders::_1    // error
        )
    );
}

void TcpClient::send(const std::string &data) {
    Packet packet(data);
    packet.encode_header();

    io_service_->post(std::bind(&TcpClient::do_write, this, packet));
}

void TcpClient::close() {
    io_service_->post(std::bind(&TcpClient::do_close, this));
}
