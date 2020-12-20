/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/
#include <math.h>
#include <map>

#include "SDL.h"
#include "include/World.hpp"
#include "include/Animations.hpp"

World::World(unsigned int _width, unsigned int _height, SDL_Texture* _bgTexture, SDL_Texture* _bgVignetteTexture):
    width(_width), height(_height), bgTexture(_bgTexture), bgVignetteTexture(_bgVignetteTexture) {
    ;
}

World::~World () {
    for (auto itr: entities)
        delete itr.second;
}

void World::addEntity(int id, Entity* entity) {
    entities.insert(std::pair<const int, Entity*>(id, entity));
}
void World::addAnimation(Animation* animation) {
    animations.push_back(animation);
}

void World::setTarget(std::map<int, Entity*> _target, unsigned int _time) {
    lastTarget = target; //entities;
    target = _target;
    timeLastTarget = timeTarget;
    timeTarget = _time;
}

void World::render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angle) {
    float radAngle = -centerRotation/180*M_PI;

    int widthBg = width;
    int heightBg = height;
    int y = - (int)centerY % heightBg - heightBg;
    if (centerY < 0)
        y -= heightBg;
    int startX = - (int)centerX % widthBg - widthBg;
    if (centerX < 0)
        startX -= widthBg;
    while (y < (centerY-baseY)*2 + heightBg) {
        int yRes = (baseY+y >= 0 ? (int)(baseY+y)/heightBg : (int)(baseY+y)/heightBg-1) % 2;
        int x = startX;
        while (x < (centerX-baseX)*2 + widthBg) {
            int xRes = (baseX+x >= 0 ? (int)(baseX+x)/widthBg : (int)(baseX+x)/widthBg-1) % 2;
            int resX = x*cos(radAngle) - y*sin(radAngle);
            int resY = x*sin(radAngle) + y*cos(radAngle);
            SDL_Rect render_rect {resX-1, resY-1, widthBg+1, heightBg+1};
            if (xRes % 2 == 0) {
                if (yRes % 2 == 0)
                    SDL_RenderCopyEx(renderer, bgTexture, NULL, &render_rect, 180 - centerRotation, NULL, SDL_FLIP_NONE);
                else
                    SDL_RenderCopyEx(renderer, bgTexture, NULL, &render_rect, -centerRotation, NULL, SDL_FLIP_HORIZONTAL);
            } else {
                if (yRes % 2 == 0)
                    SDL_RenderCopyEx(renderer, bgTexture, NULL, &render_rect, -centerRotation, NULL, SDL_FLIP_VERTICAL);
                else
                    SDL_RenderCopyEx(renderer, bgTexture, NULL, &render_rect, -centerRotation, NULL, SDL_FLIP_NONE);
            }
            x += widthBg;
        }
        y += heightBg;
    }
    SDL_Rect render_rect {0, 0, (int)(width), (int)(height)};
    SDL_RenderCopy(renderer, bgVignetteTexture, NULL, &render_rect);

    for (auto itr: animations) {
        itr->render(renderer, baseX, baseY, centerRotation, centerX, centerY, angle);
    }

    for (auto itr: entities) {
        itr.second->render(renderer, baseX, baseY, centerRotation, centerX, centerY, altitude, angle);
    }
}

void World::update(unsigned int time) {
    for (auto itr = animations.begin(); itr != animations.end(); itr++) {
        if (!(*itr)->update()) {
            animations.erase(itr--);
        }
    }

    auto targetEnd = target.end();
    auto lastTargetEnd = lastTarget.end();
    float percentage = ((float)(time-timeLastTarget))/((float)(timeTarget-timeLastTarget));
    for (auto itr = entities.begin(); itr != entities.end(); itr++) {
        auto targetItr = target.find(itr->first);
        auto lastTargetItr = lastTarget.find(itr->first);
        if (targetItr != targetEnd && lastTargetItr != lastTargetEnd)
            itr->second->updateToTarget(lastTargetItr->second, targetItr->second, percentage);
        else
            if (!itr->second->update()) {
                for (auto ani = animations.begin(); ani != animations.end(); ani++)
                    if (itr->second == (*ani)->getTarget())
                        (*ani)->setTarget(NULL);
                entities.erase(itr--);
            }
    }
}

bool World::isInEntities(int key) {
    return entities.find(key) != entities.end();
}
