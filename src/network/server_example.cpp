/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include <iostream>
#include <string>

#include "include/TcpServer.hpp"

class Server {
 private:
    TcpServer net_server;

 public:
    Server(int port): net_server(port,
            std::bind(
                &Server::net_event_callback,
                this,
                std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3
            )
        ) {}
    void start() { net_server.start(); }

    void net_event_callback(NetEventType::NetEventType ev_type, unsigned uid, std::string data) {
        if (ev_type == NetEventType::CONNECTED) {
            std::cout << "User " << uid << " connected!" << std::endl;
        } else if (ev_type == NetEventType::RECEIVED) {
            std::cout << "Received from " << uid << ": " << data << std::endl;
            net_server.send_all(data);
        } else if (ev_type == NetEventType::DISCONNECTED) {
            std::cout << "User " << uid << " disconnected!" << std::endl;
        }
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./<path_to_bin> <port>\n";
        return 1;
    }

    Server s(std::stoi(argv[1]));

    std::cout << "Server started!" << std::endl;
    s.start();

    return 0;
}
