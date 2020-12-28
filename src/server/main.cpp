/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include <iostream>
#include <string>

#include "include/ServerApp.hpp"

const char VERSION[] = "0.2.1";
const int DEFAULT_PORT = 23000;
const int DEFAULT_NOTIFY_RATE = 15;

int main(int argc, char **argv) {
    std::cout << "LK 2D Shooter server (v. " << VERSION << ") by LioKor Team";
    std::cout << std::endl;

    ServerApp server_app(DEFAULT_PORT, DEFAULT_NOTIFY_RATE);

    std::cout << "Starting server at ";
    std::cout << "0.0.0.0:" << DEFAULT_PORT << std::endl;

    server_app.start();

    return 0;
}
