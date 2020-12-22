/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/
#include <iostream>
#include <string>

#include "include/Game.hpp"


int main(int argc, char **argv) {
    std::string IP, port;
    if (argc == 1) {
        IP = "localhost";
        port = "23000";
    } else if (argc == 3) {
        IP = argv[1];
        port = argv[2];
    } else {
        std::cout << "EROOR: Invalid arguments. Must be: <IP-addr> <port>" << std::endl;
    }
    Game game("LioKor shooter", 1000, 500, IP, port);
    if (game.start()) {
        std::cout << "ERROR: Unable to start the game." << std::endl;
    }

    return 0;
}
