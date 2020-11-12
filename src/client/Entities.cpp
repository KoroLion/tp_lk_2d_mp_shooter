/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#include <iostream>
#include <math.h>

#include "SDL.h"
#include "include/Entities.hpp"


void Entity::render(SDL_Renderer *renderer) {
    if (texture != NULL) {
        SDL_Rect render_rect {(int)x, (int)y, (int)width, (int)height};
        SDL_RenderCopyEx(renderer, texture, NULL, &render_rect, rotation, NULL, SDL_FLIP_NONE);
    }
}

void Entity::update() {
    x += 1;
    y += sin(x / 10);
    rotation += 1;
}
