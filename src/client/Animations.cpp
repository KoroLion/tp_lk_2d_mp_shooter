/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include <math.h>

#include "include/Animations.hpp"
#include "include/Entities.hpp"
#include "SDL.h"

void LightTrasser::render(SDL_Renderer* renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float angle) {
    if (texture == NULL)
        return;

    float radAngle = -centerRotation/180*M_PI;
    float difX = x - centerX;
    float difY = y - centerY;
    float resX = difX*cos(radAngle) - difY*sin(radAngle);
    float resY = difX*sin(radAngle) + difY*cos(radAngle);
    resX += centerX - baseX;
    resY += centerY - baseY;

    float difXEnd = xEnd - centerX;
    float difYEnd = yEnd - centerY;
    float resXEnd = difXEnd*cos(radAngle) - difYEnd*sin(radAngle);
    float resYEnd = difXEnd*sin(radAngle) + difYEnd*cos(radAngle);
    resXEnd += centerX - baseX;
    resYEnd += centerY - baseY;

    centerRotation = rotation - centerRotation; // now it's absolute rotation

    const float patterns = 2;
    int texture_w, texture_h;
    SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h);
    int widthOfOne = (float)height * texture_w/texture_h;
    float wDif = texture_w / patterns;
    float clipX = 0;
    float width = distance(resX,resY, resXEnd,resYEnd);
    float global_patterns = width / widthOfOne * patterns;
    float xDif = (resXEnd - resX) / global_patterns;
    float yDif = (resYEnd - resY) / global_patterns;
    width /= global_patterns;
    float dist;
    for (int i = 0; i < global_patterns; i++) {
        if ((dist = distance(resX, resY, resXEnd,resYEnd)) < 300) {
            SDL_SetTextureAlphaMod(texture, 0xFF * (1 - dist/300));
            SDL_Rect clip_rect {(int)(clipX), 0, (int)(clipX + wDif), (int)(texture_h)};
            SDL_Rect render_rect {(int)(resX), (int)(resY), (int)(width), (int)(height)};
            SDL_Point rotatePoint {0, 0};
            SDL_RenderCopyEx(renderer, texture, &clip_rect, &render_rect, centerRotation, &rotatePoint, SDL_FLIP_NONE);
        }
        resX += xDif;
        resY += yDif;
        clipX = wDif * (i % (int)patterns);
    }
    SDL_SetTextureAlphaMod(texture, 0xFF);
}

bool LightTrasser::update() {
    float radRot = rotation/180*M_PI;
    xEnd = target->getX() - target->getWidth()/2*cos(radRot) + height/2*sin(radRot);
    yEnd = target->getY() - target->getWidth()/2*sin(radRot) - height/2*cos(radRot);
    timer++;
    return true;
}
