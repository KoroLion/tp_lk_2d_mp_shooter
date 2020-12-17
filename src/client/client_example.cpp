#include <iostream>
#include <Windows.h>

#include "include/TcpClient.hpp"

DWORD WINAPI input_handler(void* param) {
    TcpClient *c = (TcpClient*)param;

    std::string line;

    std::cout << "Waiting for input..." << std::endl;
    while (std::getline(std::cin, line)) {
        c->send(line);
    }

    c->close();

    return 0;
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: TcpClient <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(argv[1], argv[2]);
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
        TcpClient c(&io_service, iterator);

        HANDLE ht = CreateThread(
            NULL,
            0,
            input_handler,
            &c,
            0,
            NULL
        );
        if (ht == NULL) {
            throw std::exception();
        }

        io_service.run();

        WaitForSingleObject(ht, INFINITE);
        CloseHandle(ht);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
