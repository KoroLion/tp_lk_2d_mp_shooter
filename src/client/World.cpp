/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/
#include <iostream>
#include <vector>

#include "SDL.h"
#include "include/World.hpp"

World::World(int _width, int _height): width(_width), height(_height) {
;
}

World::~World () {
    for (auto itr = entities.begin(); itr < entities.end(); itr++)
        delete *itr;
}

void World::addEntity(Entity* entity) {
    entities.push_back(entity);
}

void World::render(SDL_Renderer *renderer) {
    for (auto itr = entities.begin(); itr < entities.end(); itr++) {
        (*itr)->render(renderer);
    }
}

void World::update() {
    for (auto itr = entities.begin(); itr < entities.end(); itr++) {
        (*itr)->update();
    }
}

