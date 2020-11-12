#include <iostream>
#include <string>

#include "include/ServerApp.hpp"

const std::string VERSION = "0.1.0";

int main(int argc, char **argv) {
    std::cout << "LK 2D Shooter server (v. " << VERSION << ") by LioKor Team";
    std::cout << std::endl;

    ServerApp server_app;
    server_app.start();

    return 0;
}
