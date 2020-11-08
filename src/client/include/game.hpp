/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_GAME_HPP_
#define SRC_CLIENT_INCLUDE_GAME_HPP_

#include <string>

#include "SDL.h"
#include "Entities.hpp"
#include "World.hpp"

class Game {
 public:
    std::string title;
    int width, height;

    Game(std::string title, int width, int height);

    bool start();
    void stop() { this->is_running = false; }

    ~Game();

 private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    void handle_event(SDL_Event);
    void update();
    void render();

    bool isRunning;

    Player* thisPlayer;
    World* world;
};

#endif  // SRC_CLIENT_INCLUDE_GAME_HPP_
