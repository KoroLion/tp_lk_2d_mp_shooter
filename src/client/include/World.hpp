/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_WORLD_HPP_
#define SRC_CLIENT_INCLUDE_WORLD_HPP_

#include <math.h>
#include <vector>

#include "SDL.h"
#include "Entities.hpp"

class World {
 public:
    World(int _width, int _height);
    ~World();

    void render(SDL_Renderer *renderer);
    void update();
    void addEntity(Entity* entity);

 private:
    std::vector<Entity*> entities;
    int width, height;
};

#endif  // SRC_CLIENT_INCLUDE_WORLD_HPP_
