
/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#include <iostream>
#include <string>

#include "include/game.hpp"

int main(int argc, char **argv) {
    Game game("LK 2D Shooter", 640, 480);
    if (game.start()) {
        std::cout << "ERROR: Unable to start the game!" << std::endl;
    }

    return 0;
}
