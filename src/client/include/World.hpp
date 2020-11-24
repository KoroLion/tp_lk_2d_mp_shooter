/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_WORLD_HPP_
#define SRC_CLIENT_INCLUDE_WORLD_HPP_

#include <map>

#include "SDL.h"
#include "Entities.hpp"

class World {
 public:
    World(unsigned int _width, unsigned int _height);
    ~World();

    void render(SDL_Renderer *renderer, float baseX = 0, float baseY = 0, float centerRotation = 0, float centerX = 0, float centerY = 0, float altitude = 10, float angle = 60);
    void update(unsigned int time);
    void addEntity(int id, Entity* entity);
    void deleteEntity(int id);
    void setTarget(std::map<int, Entity*>* _target, unsigned int _time);

 private:
    std::map<int, Entity*> entities;
    std::map<int, Entity*> *target = NULL, *lastTarget = NULL;
    unsigned int timeTarget, timeLastTarget;
    unsigned int width, height;
};

#endif  // SRC_CLIENT_INCLUDE_WORLD_HPP_
