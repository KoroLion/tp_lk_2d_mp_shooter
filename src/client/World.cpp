/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/
#include <math.h>
#include <map>

#include "SDL.h"
#include "include/World.hpp"
#include "include/Animations.hpp"
#include "include/Colors.hpp"

extern void drawLine(SDL_Renderer* renderer, float x1, float y1, float x2, float y2, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

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

void World::render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angle, int widthBg, int heightBg) {
    float radAngle = -centerRotation/180*M_PI;

    //int widthBg = width;
    //int heightBg = height;
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
    // border
    float difX0 = 0 - centerX;
    float difY0 = 0 - centerY;
    float resX0 = difX0*cos(radAngle) - difY0*sin(radAngle) + centerX - baseX;
    float resY0 = difX0*sin(radAngle) + difY0*cos(radAngle) + centerY - baseY;
    float difX1 = width - centerX;
    float difY1 = 0 - centerY;
    float resX1 = difX1*cos(radAngle) - difY1*sin(radAngle) + centerX - baseX;
    float resY1 = difX1*sin(radAngle) + difY1*cos(radAngle) + centerY - baseY;
    float difX2 = width - centerX;
    float difY2 = height - centerY;
    float resX2 = difX2*cos(radAngle) - difY2*sin(radAngle) + centerX - baseX;
    float resY2 = difX2*sin(radAngle) + difY2*cos(radAngle) + centerY - baseY;
    float difX3 = 0 - centerX;
    float difY3 = height - centerY;
    float resX3 = difX3*cos(radAngle) - difY3*sin(radAngle) + centerX - baseX;
    float resY3 = difX3*sin(radAngle) + difY3*cos(radAngle) + centerY - baseY;
    drawLine(renderer, resX0,resY0, resX1,resY1, 5, RED_RGB, 0x33);
    drawLine(renderer, resX1,resY1, resX2,resY2, 5, RED_RGB, 0x33);
    drawLine(renderer, resX2,resY2, resX3,resY3, 5, RED_RGB, 0x33);
    drawLine(renderer, resX3,resY3, resX0,resY0, 5, RED_RGB, 0x33);
    drawLine(renderer, resX0,resY0, resX1,resY1, 2, ORANGE_RGB, 0x33);
    drawLine(renderer, resX1,resY1, resX2,resY2, 2, ORANGE_RGB, 0x33);
    drawLine(renderer, resX2,resY2, resX3,resY3, 2, ORANGE_RGB, 0x33);
    drawLine(renderer, resX3,resY3, resX0,resY0, 2, ORANGE_RGB, 0x33);
    // vignette
    SDL_Rect render_rect {0, 0, (int)(width), (int)(height)};
    SDL_RenderCopy(renderer, bgVignetteTexture, NULL, &render_rect);

    for (auto itr: animations) {
        itr->render(renderer, baseX, baseY, centerRotation, centerX, centerY, angle);
    }

    for (auto itr: entities) {
        itr.second->render(renderer, baseX, baseY, centerRotation, centerX, centerY, altitude, angle);
    }
}

void World::update(time_t &time, Entity* ignore) {
    if (time < timeLastTarget)
        time = timeLastTarget;
    if (timeTarget-timeLastTarget == 0)
        return;
    auto targetEnd = target.end();
    auto lastTargetEnd = lastTarget.end();
    float percentage = ((float)(time-timeLastTarget))/((float)(timeTarget-timeLastTarget));

    for (auto itr = animations.begin(); itr != animations.end(); itr++) {
        if (!(*itr)->update()) {
            delete (*itr);
            animations.erase(itr--);
        }
    }

    int i = 0;
    for (auto itr = entities.begin(); itr != entities.end(); itr++) {
        i++;
        if (itr->second == ignore)
            ;//continue;
        auto targetItr = target.find(itr->first);
        auto lastTargetItr = lastTarget.find(itr->first);
        if (targetItr != targetEnd && lastTargetItr != lastTargetEnd) {
            //SDL_Log("Perc: %f", percentage);
            itr->second->updateToTarget(lastTargetItr->second, targetItr->second, percentage);
        } else {
            if (!itr->second->update()) {
                for (auto ani = animations.begin(); ani != animations.end(); ani++)
                    if (itr->second == (*ani)->getTarget())
                        (*ani)->setTarget(NULL);

                delete itr->second;
                entities.erase(itr--);
            }
        }
    }
}

Entity* World::getEntity(int key) {
    auto itr = entities.find(key);
    if (itr == entities.end())
        return NULL;
    return itr->second;
}
