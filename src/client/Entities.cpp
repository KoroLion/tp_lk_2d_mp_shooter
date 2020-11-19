/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include <iostream>
#include <math.h>

#include "SDL.h"
#include "include/Entities.hpp"


void Entity::render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY) {
    if (texture == NULL)
        return;
    float radAngle = -centerRotation/180*M_PI;
    float difX = x - centerX;
    float difY = y - centerY;
    float resX = difX*cos(radAngle) - difY*sin(radAngle);
    float resY = difX*sin(radAngle) + difY*cos(radAngle);
    resX = centerX + resX - width/2;
    resY = centerY + resY - height/2;

    SDL_Rect render_rect {(int)(resX - baseX), (int)(resY - baseY), (int)width, (int)height};
    SDL_Point centerPoint {(int)(width/2), (int)(height/2)};
    SDL_RenderCopyEx(renderer, texture, NULL, &render_rect, rotation - centerRotation, &centerPoint, SDL_FLIP_NONE);
}

void Entity::updateToTarget(Entity* lastTarget, Entity* target, float percentage) {
    //x += 1;
    //y += sin(x / 10);
    //rotation += 1;
    x = (target->x - lastTarget->x)*percentage + lastTarget->x;
    y = (target->y - lastTarget->y)*percentage + lastTarget->y;
    rotation = (target->rotation - lastTarget->rotation)*percentage + lastTarget->rotation;

    width = (target->width - lastTarget->width)*percentage + lastTarget->width;
    height = (target->height - lastTarget->height)*percentage + lastTarget->height;
}

void Entity::moveAngledAbsolute(float toForward, float toSide, float absoluteAngle) {
    x += toForward * cos(absoluteAngle/180*M_PI);
    y += toForward * sin(absoluteAngle/180*M_PI);
    x += toSide * sin(absoluteAngle/180*M_PI);
    y += toSide * cos(absoluteAngle/180*M_PI);
}

void Player::moveRelative(float addAngle) {
    x += speed * cos((addAngle + rotation)/180*M_PI);
    y += speed * sin((addAngle + rotation)/180*M_PI);
}
