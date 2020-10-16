/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_GAME_HPP_
#define SRC_CLIENT_INCLUDE_GAME_HPP_

#include <math.h>
#include <string>
#include <vector>

#include "SDL.h"
#include "game_objects.hpp"

class Game {
 private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    void handle_event(SDL_Event);
    void update();
    void render();

    bool is_running;

    std::vector<GameObject*> game_objects;
 public:
    std::string title;
    int width, height;

    Game(std::string title, int width, int height);
    ~Game();

    bool start();
    void stop() { this->is_running = false; }
};

#endif  // SRC_CLIENT_INCLUDE_GAME_HPP_
