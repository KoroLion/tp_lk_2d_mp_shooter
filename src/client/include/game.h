/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_GAME_H_
#define SRC_CLIENT_INCLUDE_GAME_H_

#include <vector>
#include <math.h>

#include "SDL.h"

class GameObject {
public:
    float x, y;
    
    GameObject(int x, int y) {
        this->x = x;
        this->y = y;
    }
    
    virtual void render(SDL_Renderer *renderer) {
        // Drawing green rect with black border
        SDL_Rect r;
        r.x = this->x; r.y = this->y; r.w = 50; r.h = 50;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // rgba
        SDL_RenderFillRect(renderer, &r);
        SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
        SDL_RenderDrawRect(renderer, &r);
    }
    
    virtual void update() {
        this->x += 0.5;
        this->y = sin(this->x / 10) * 100 + 100;
    }
};

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

#endif  // SRC_CLIENT_INCLUDE_GAME_H_