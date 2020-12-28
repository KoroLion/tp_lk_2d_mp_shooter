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
    Animation(Entity* _target, float _x, float _y, SDL_Texture* _texture):
        target(_target), x(_x), y(_y), texture(_texture), timer(0) {;}

    virtual void render(SDL_Renderer* renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float angle) {;}
    virtual bool update() {return true;}

    Entity* getTarget() {return target;}

    void setTarget(Entity* newTarget) {target = newTarget;}

    virtual ~Animation() {;}

protected:
    Entity* target;
    float x, y;
    SDL_Texture* texture;
    time_t timer;
};

class LightTrasser: public Animation {
public:
    LightTrasser(Entity* _target, float _x, float _y, int _height, float _rotation, SDL_Texture* _texture);

    virtual void render(SDL_Renderer* renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float angle);
    virtual bool update();

    ~LightTrasser() {;}

protected:
    const int timeToFade = 100;
    const float patterns = 3;
    float xEnd, yEnd;
    int width;
    float rotation;
    std::vector<int> partTimes;
    std::vector<std::pair<float, float>> parts;
    float partWidth;
};

#endif // SRC_CLIENT_INCLUDE_ANIMATIONS_HPP_
