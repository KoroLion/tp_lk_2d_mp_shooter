#include <iostream>
#include <Windows.h>

#include "include/common.hpp"
#include "include/TcpClient.hpp"

#include "lib/json.hpp"
using json = nlohmann::json;


class Client {
 private:
    TcpClient net_client;

    std::string first_message;
    std::string last_message;

    DWORD net_handler() {
        net_client.connect();

        return 0;
    }
 public:
    Client(std::string host, std::string port):
        net_client(host, port, std::bind(
            net_event_callback,
            this,
            std::placeholders::_1,
            std::placeholders::_2
        )) {};

    static void static_net_handler(void* p) {
        ((Client*)p)->net_handler();
    }

    void net_event_callback(NetEventType::NetEventType ev_type, std::string data) {
        if (ev_type == NetEventType::CONNECTED) {
            std::cout << "CONNECTED" << std::endl;
        } else if (ev_type == NetEventType::RECEIVED) {
            if (first_message.length() == 0) {
                first_message = data;
            }
            last_message = data;
        } else if (ev_type == NetEventType::DISCONNECTED) {
            std::cout << "DISCONNECTED" << std::endl;
        }
    }

    void start() {
        try {
            HANDLE ht = CreateThread(
                NULL,
                0,
                (LPTHREAD_START_ROUTINE)static_net_handler,
                this,
                0,
                NULL
            );
            if (ht == NULL) {
                throw std::exception();
            }

            std::string line;

            std::cout << "Connecting... ";
            while (!net_client.is_connected()) {}

            while (net_client.is_connected()) {
                std::cout << "Input is not displayed. Type 'stop' or 'last'. Double-tap Enter to submit input: ";
                std::cin >> line;
                std::cout << line << std::endl;
                if (line == "stop") {
                    net_client.close();
                    break;
                } else if (line == "last") {
                    std::cout << last_message << std::endl;
                } else if (line == "first") {
                    std::cout << first_message << std::endl;
                } else {
                    net_client.send(line);
                }
            }

            WaitForSingleObject(ht, INFINITE);
            CloseHandle(ht);
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: TcpClient <host> <port>\n";
        return 1;
    }

    Client client(argv[1], argv[2]);
    client.start();

    return 0;
}
