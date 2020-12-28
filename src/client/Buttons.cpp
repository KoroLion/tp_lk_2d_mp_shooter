/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include "SDL.h"
#include "SDL_TTF.h"

#include "include/Buttons.hpp"

void renderText(SDL_Renderer* renderer, const char* text,
                int x, int y, TTF_Font* font, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, {r, g, b, a});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int textureW, textureH;
    SDL_QueryTexture(texture, NULL, NULL, &textureW, &textureH);
    SDL_Rect rect{x - textureW / 2, y - textureH / 2, textureW, textureH};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
}

void Button::render(SDL_Renderer *renderer) {
    if (!defaultTexture || !onMoveTexture || !onClickTexture)
        return;

    SDL_Rect render_rect {x - width/2, y - height/2, width, height};
    switch(condition) {
    case UP:
        SDL_RenderCopy(renderer, defaultTexture, NULL, &render_rect);
        break;
    case ONMOVE:
        SDL_RenderCopy(renderer, onMoveTexture, NULL, &render_rect);
        break;
    case DOWN:
        SDL_RenderCopy(renderer, onClickTexture, NULL, &render_rect);
        break;
    }
    renderText(renderer, text, x, y, font, r,g,b,a);
}

void Button::update(int xc, int yc, bool buttonPress) {
    if (isInside(xc, yc)) {
        if (buttonPress) {
            condition = DOWN;
        } else {
            if (condition == DOWN)
                onClick();
            condition = ONMOVE;
        }
    } else {
        condition = UP;
    }
}
