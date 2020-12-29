/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_GAME_OBJECTS_HPP_
#define SRC_CLIENT_INCLUDE_GAME_OBJECTS_HPP_

#include <math.h>
#include <vector>

#include "SDL.h"

class GameObject {
 public:
    float x, y;

    GameObject(int x, int y): x(x), y(y) {}
    virtual ~GameObject() {}

    virtual void render(SDL_Renderer *renderer) {}
    virtual void update() {}
};

class SmallRect: public GameObject {
 public:
    SmallRect(int x, int y): GameObject(x, y) {}
    virtual void render(SDL_Renderer *renderer);
};

class MovingRect: public GameObject {
 public:
    int width, height;
    float speed;

    MovingRect(int x, int y, int w, int h, float speed = 0): GameObject(x, y),
        width(w), height(h), speed(speed) {}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();
};

#endif  // SRC_CLIENT_INCLUDE_GAME_OBJECTS_HPP_
