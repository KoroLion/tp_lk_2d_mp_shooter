/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include <iostream>

#include "SDL.h"
#include "include/Camera.hpp"
#include "include/Entities.hpp"


void Camera::render(SDL_Renderer *renderer) {
    world->render(renderer, x - width/2, y - height/2, rotation, x, y);
}

void Camera::update() {
    if (target == NULL)
        return;

    x += (target->getX() - x)*0.05;
    y += (target->getY() - y)*0.05;
    if (seek_rotation)
        rotation += (target->getRotation() - rotation + 90)*0.05;
    /*
    if (target->getX() - x < 20)
        x += (20 - target->getX() + x)*0.05;
    if (target->getY() - y < 20)
        y += (20 - target->getX() + y)*0.05;

    if (target->getX() - x < 2)
        x += (target->getX() - x)*0.2;
    if (target->getY() - y < 2)
        y += (target->getX() - y)*0.2;
    */
}

