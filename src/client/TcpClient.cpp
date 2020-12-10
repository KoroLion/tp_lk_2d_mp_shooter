#include <cstdlib>
#include <deque>
#include <iostream>

#include <thread>

#include <boost/asio.hpp>

#include "include/Packet.hpp"

typedef std::deque<Packet> Packet_queue;

class TcpClient {
 public:
    TcpClient(boost::asio::io_service *io_service, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
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

    void send(const Packet& packet) {
        io_service_->post(std::bind(&TcpClient::do_write, this, packet));
    }

    void close() {
        io_service_->post(std::bind(&TcpClient::do_close, this));
    }

 private:
    void handle_connect(const boost::system::error_code& error) {
        if (!error) {
            std::cout << "CONNECTED!" << std::endl;
            read_header();
        }
    }

    void read_header() {
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

    void read_body() {
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

    void handle_read_header(const boost::system::error_code& error) {
        if (!error && read_packet_.decode_header()) {
            read_body();
        } else {
            do_close();
        }
    }

    void handle_read_body(const boost::system::error_code& error) {
        if (!error) {
            std::cout << read_packet_.get_as_string() << std::endl;
            read_header();
        } else {
            do_close();
        }
    }

    void write_next() {
        boost::asio::async_write(socket_,
            boost::asio::buffer(write_packets_.front().get_data(), write_packets_.front().size()),
            std::bind(
                &TcpClient::handle_write,
                this,
                std::placeholders::_1    // error
            )
        );
    }

    void do_write(Packet packet) {
        bool write_in_progress = !write_packets_.empty();
        write_packets_.push_back(packet);
        if (!write_in_progress) {
            write_next();
        }
    }

    void handle_write(const boost::system::error_code& error) {
        if (!error) {
            write_packets_.pop_front();
            if (!write_packets_.empty()) {
                write_next();
            }
        } else {
            do_close();
        }
    }

    void do_close() {
        std::cout << "DISCONNECTED" << std::endl;
        socket_.close();
    }

 private:
    boost::asio::io_service *io_service_;
    boost::asio::ip::tcp::socket socket_;
    Packet read_packet_;
    Packet_queue write_packets_;
};

void input_handler(TcpClient *c, std::string username) {
    std::string line;

    while (std::getline(std::cin, line)) {
        line = username + ": " + line;
        Packet packet(line);
        packet.encode_header();
        c->send(packet);
    }

    c->close();
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 4) {
            std::cerr << "Usage: TcpClient <host> <port> <username>\n";
            return 1;
        }
        boost::asio::io_service io_service;

        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(argv[1], argv[2]);
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

        std::string username(argv[3]);

        TcpClient c(&io_service, iterator);

        std::thread t(&input_handler, &c, username);
        io_service.run();
        t.join();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
