#include <iostream>
#include "include/constants.hpp"
#include "include/TcpServer.hpp"

class Server {
 private:
    TcpServer net_server;
 public:
    Server(): net_server(23001,
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
            std::cout << "Player " << uid << " connected!" << std::endl;
        } else if (ev_type == NetEventType::RECEIVED) {
            std::cout << "Received from " << uid << ": " << data << std::endl;
        } else if (ev_type == NetEventType::DISCONNECTED) {
            std::cout << "Player " << uid << " disconnected!" << std::endl;
        }
    }
};

int main() {
    Server s;
    s.start();
}
