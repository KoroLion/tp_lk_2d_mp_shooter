/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include <iostream>
#include <string>

#include "include/ServerApp.hpp"

const char VERSION[] = "0.2.0";
const char DEFAULT_BIND_ADDR[] = "0.0.0.0";
const int DEFAULT_PORT = 23000;

int main(int argc, char **argv) {
    std::cout << "LK 2D Shooter server (v. " << VERSION << ") by LioKor Team";
    std::cout << std::endl;

    ServerApp server_app(DEFAULT_BIND_ADDR, DEFAULT_PORT);

    std::cout << "Starting server at ";
    std::cout << DEFAULT_BIND_ADDR << ":" << DEFAULT_PORT << std::endl;

    server_app.start();

    return 0;
}
