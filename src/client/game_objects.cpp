/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#include "SDL.h"
#include "include/game_objects.hpp"

void SmallRect::render(SDL_Renderer *renderer) {
    // Drawing green rect with black border
    SDL_Rect r{(int)this->x, (int)this->y, 32, 32};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // rgba
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
    SDL_RenderDrawRect(renderer, &r);
}

void MovingRect::render(SDL_Renderer *renderer) {
    // Drawing green rect with black border
    SDL_Rect r{(int)this->x, (int)this->y, this->width, this->height};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // rgba
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
    SDL_RenderDrawRect(renderer, &r);
}

void MovingRect::update() {
    if (this->x >= 320 && this->speed > 0) {
        this->speed = -this->speed;
    } else if (this->x < 0) {
        this->speed = -this->speed;
    }

    this->x += this->speed;
    this->y = sin(this->x / 10) * 100 + 200;
}
