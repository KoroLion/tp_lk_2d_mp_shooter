/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include <iostream>
#include <thread>

#include "include/TcpClient.hpp"

class Client {
 private:
    TcpClient net_client;
    std::thread net_client_thread;

 public:
    Client(std::string host, std::string port):
        net_client(host, port, std::bind(
            &Client::net_event_callback,
            this,
            std::placeholders::_1,
            std::placeholders::_2
        )) {}

    void net_client_handler() {
        net_client.connect();
    }

    void net_event_callback(NetEventType::NetEventType ev_type, std::string data) {
        if (ev_type == NetEventType::CONNECTED) {
            std::cout << "Connected!" << std::endl;
        } else if (ev_type == NetEventType::RECEIVED) {
            std::cout << "Received: " << data << std::endl;
        } else if (ev_type == NetEventType::DISCONNECTED) {
            std::cout << "Disconnected!" << std::endl;
        }
    }

    void start() {
        net_client_thread = std::thread(&Client::net_client_handler, this);

        std::string line;

        std::cout << "Connecting..." << std::endl;
        while (!net_client.is_connected()) {}

        while (net_client.is_connected()) {
            std::cin >> line;
            net_client.send(line);
        }

        net_client_thread.join();
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./<path_to_bin> <host> <port>\n";
        return 1;
    }

    Client client(argv[1], argv[2]);
    client.start();

    return 0;
}
