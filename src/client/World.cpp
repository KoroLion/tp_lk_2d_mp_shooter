/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/
#include <iostream>
#include <map>

#include "SDL.h"
#include "include/World.hpp"

World::World(unsigned int _width, unsigned int _height): width(_width), height(_height) {
;
}

World::~World () {
    for (auto itr: entities)
        delete itr.second;
}

void World::addEntity(int id, Entity* entity) {
    entities.insert(std::pair<const int, Entity*>(id, entity));
}

void World::deleteEntity(int id) {
    entities.erase(id);
}

void World::setTarget(std::map<int, Entity*>* _target, unsigned int _time) {
    if (lastTarget != NULL)
        delete lastTarget;
    lastTarget = target;
    target = _target;
    timeLastTarget = timeTarget;
    timeTarget = _time;
}

void World::render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY) {
    for (auto itr: entities) {
        itr.second->render(renderer, baseX, baseY, centerRotation, centerX, centerY);
    }
}

void World::update(unsigned int time) {
    auto targetEnd = (*target).end();
    auto lastTargetEnd = (*lastTarget).end();
    float percentage = ((float)(time-timeLastTarget))/((float)(timeTarget-timeLastTarget));
    for (auto itr: entities) {
        auto targetItr = (*target).find(itr.first);
        auto lastTargetItr = (*lastTarget).find(itr.first);
        if (targetItr != targetEnd && lastTargetItr != lastTargetEnd)
            itr.second->updateToTarget(lastTargetItr->second, targetItr->second, percentage);
        itr.second->update();
    }
}

