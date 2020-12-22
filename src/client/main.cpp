/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/
#include <iostream>
#include <string>

#include "include/Game.hpp"


int main(int argc, char **argv) {
    Game game("LioKor shooter", 1000, 500);
    if (game.start()) {
        std::cout << "ERROR: Unable to start the game!" << std::endl;
    }

    return 0;
}
