/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_GAME_HPP_
#define SRC_CLIENT_INCLUDE_GAME_HPP_

#include <vector>

#include "SDL.h"
#include "Entities.hpp"
#include "World.hpp"

#define BOX_TEXTURE_ID 0

SDL_Texture* loadTexture(const char* imgName, SDL_Renderer* renderer, SDL_Surface* win_surf);

class Game {
 public:
    const char* title;
    int width, height;

    Game(const char* title, int width, int height);

    bool start();
    void stop() { this->isRunning = false; }

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

    std::vector<const char*> textureNames {"res/textures/box.bmp"};
    std::vector<SDL_Texture*> textures;
};

#endif  // SRC_CLIENT_INCLUDE_GAME_HPP_
