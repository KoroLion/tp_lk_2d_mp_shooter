/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_GAME_HPP_
#define SRC_CLIENT_INCLUDE_GAME_HPP_

#include <vector>

#include "SDL.h"
#include "World.hpp"
#include "Camera.hpp"

#define BOX_TEXTURE_ID 0

SDL_Texture* loadTexture(const char* imgName, SDL_Renderer* renderer, SDL_Surface* win_surf);

class Game {
 public:
    Game(const char* title, int width, int height);

    bool start();
    void stop() { this->isRunning = false; }

    ~Game();

 private:
    const char* title;
    int width, height;
    unsigned int time;

    SDL_Window *window;
    SDL_Renderer *renderer;

    void handleEvent(SDL_Event);
    void keyboardEvents();
    void update();
    void render();

    bool isRunning;

    Player* player;
    World* world;
    Camera* camera;

    std::vector<const char*> textureNames {"res/textures/box.bmp"};
    std::vector<SDL_Texture*> textures;
};

#endif  // SRC_CLIENT_INCLUDE_GAME_HPP_
