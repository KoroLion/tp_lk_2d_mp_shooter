/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_ANIMATIONS_HPP_
#define SRC_CLIENT_INCLUDE_ANIMATIONS_HPP_

#include <math.h>
#include <vector>

class Animation;

#include "SDL.h"
#include "Entities.hpp"

class Animation {
public:
    Animation(float _x, float _y, SDL_Texture* _texture):
        x(_x), y(_y), texture(_texture), timer(0) {;}

    virtual void render(SDL_Renderer* renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float angle) {;}
    virtual bool update() {return true;}

    ~Animation() {;}

protected:
    float x, y;
    time_t timer;
    SDL_Texture* texture;
};

class LightTrasser: public Animation {
public:
    LightTrasser(Entity* _target, float _x, float _y, int _height, float _rotation, SDL_Texture* _texture):
        Animation(_x, _y, _texture), target(_target), xEnd(_x), yEnd(_y), height(_height), rotation(_rotation) {;}

    virtual void render(SDL_Renderer* renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float angle);
    virtual bool update();

    ~LightTrasser() {;}

protected:
    const int timeToFade = 20;
    float xEnd, yEnd, rotation;
    int height;
    Entity* target;
};

#endif // SRC_CLIENT_INCLUDE_ANIMATIONS_HPP_
