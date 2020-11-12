#include <iostream>
#include <string>

#include "include/ServerApp.hpp"

const std::string VERSION = "0.1.0";
const std::string DEFAULT_BIND_ADDR = "0.0.0.0";
const int DEFAULT_PORT = 23000;

int main(int argc, char **argv) {
    std::cout << "LK 2D Shooter server (v. " << VERSION << ") by LioKor Team"
        << std::endl;

    ServerApp server_app(DEFAULT_BIND_ADDR, DEFAULT_PORT);
    std::cout << "Starting server at "
        << DEFAULT_BIND_ADDR << ":" << DEFAULT_PORT << std::endl;
    server_app.start();

    return 0;
}
