#include <iostream>
#include <Windows.h>

#include "include/common.hpp"
#include "include/TcpClient.hpp"

#include "lib/json.hpp"
using json = nlohmann::json;


class Client {
 private:
    TcpClient net_client;
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

    void net_event_callback(NetServerEventType ev_type, std::string data) {
        if (ev_type == CONNECTED) {
            std::cout << "CONNECTED" << std::endl;
        } else if (ev_type == MESSAGE) {
            last_message = data;
        } else if (ev_type == DISCONNECTED) {
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
                    auto j = json::parse(last_message);
                    for (auto itr = j.begin(); itr != j.end(); itr++) {
                        auto obj = *itr;

                        unsigned type_id = obj["typeId"];
                        switch (type_id) {
                            case EntityType::PLAYER:
                                std::cout << "Player at ";
                                break;
                            case EntityType::BOX_SMALL:
                                std::cout << "Small box at ";
                                break;
                            case EntityType::BOX_BIG:
                                std::cout << "Big box at ";
                                break;
                            default:
                                std::cout << "Unknown object (" << type_id << ") ";
                        }
                        std::cout << "(" << obj["x"] << ", " << obj["y"] << ")" << std::endl;
                    }
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
