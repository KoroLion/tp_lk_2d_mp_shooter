/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_WORLD_HPP_
#define SRC_CLIENT_INCLUDE_WORLD_HPP_

#include <map>
#include <vector>

class World;

#include "SDL.h"
#include "Entities.hpp"
#include "Animations.hpp"

class World {
 public:
    World(unsigned int _width, unsigned int _height, SDL_Texture* _bgTexture = NULL, SDL_Texture* _bgVignetteTexture = NULL);

    void render(SDL_Renderer *renderer, float baseX = 0, float baseY = 0, float centerRotation = 0, float centerX = 0, float centerY = 0, float altitude = 10, float angle = 60);
    void update(unsigned int time);
    void addEntity(int id, Entity* entity);
    void addAnimation(Animation* animation);
    void setTarget(std::map<int, Entity*> _target, unsigned int _time);
    Entity* getEntity(int key);

    ~World();

 private:
    std::vector<Animation*> animations;
    std::map<int, Entity*> entities;
    std::map<int, Entity*> target, lastTarget;
    unsigned int timeTarget, timeLastTarget;
    unsigned int width, height;

    SDL_Texture* bgTexture;
    SDL_Texture* bgVignetteTexture;
};

#endif  // SRC_CLIENT_INCLUDE_WORLD_HPP_
