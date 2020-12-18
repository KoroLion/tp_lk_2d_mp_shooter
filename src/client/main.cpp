#include <iostream>
#include <string>

#include "include/Game.hpp"


int main(int argc, char **argv) {
    Game game("Client.exe vsegda prav!", 1000, 500);
    if (game.start()) {
        std::cout << "ERROR: Unable to start the game!" << std::endl;
    }

    return 0;
}
