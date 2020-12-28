/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include <iostream>

#include "SDL.h"
#include "include/Camera.hpp"
#include "include/Entities.hpp"


void Camera::render(SDL_Renderer *renderer) {
    world->render(renderer, x - width/2, y - height/2, rotation, x, y, z, angle, width, height);
}

void Camera::update() {
    if (target == NULL)
        return;

    x += (target->getX() - x)*0.05;
    y += (target->getY() - y)*0.05;
    if (seek_rotation)
        rotation += (target->getRotation() - rotation + 90)*0.05;
}

