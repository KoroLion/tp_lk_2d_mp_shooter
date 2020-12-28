/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include <math.h>

#include "include/Animations.hpp"
#include "include/Entities.hpp"
#include "SDL.h"

LightTrasser::LightTrasser(Entity* _target, float _x, float _y, int _height, float _rotation, SDL_Texture* _texture):
    Animation(_target, _x, _y, _texture), xEnd(_x), yEnd(_y), width(_height), rotation(_rotation) {
    int texture_w, texture_h;
    SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h);
    partWidth = (float)width * texture_w/texture_h / patterns;

    partTimes.push_back(timeToFade);
    parts.push_back(std::pair<float, float>(xEnd, yEnd));
}

void LightTrasser::render(SDL_Renderer* renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float angle) {
    if (texture == NULL)
        return;

    float radAngle = -centerRotation/180*M_PI;
    /*float difX = x - centerX;
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
    resYEnd += centerY - baseY;*/

    centerRotation = rotation - centerRotation; // now it's absolute rotation

    int texture_w, texture_h;
    SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h);
    float wDif = texture_w / patterns;
    float clipX = 0;
    //float startWidth = distance(resX,resY, resXEnd,resYEnd);
    //float global_patterns = startWidth / partWidth * patterns;
    //float xDif = (resXEnd - resX) / global_patterns;
    //float yDif = (resYEnd - resY) / global_patterns;
    //startWidth /= global_patterns;
    //float dist;
    if (parts.size() > 0)
        clipX = ((int)(distance(parts[0].first, parts[0].second, x, y) / partWidth) % (int)patterns) * wDif;
    for (size_t i = 0; i < parts.size(); i++) {
        float difX = parts[i].first - centerX;
        float difY = parts[i].second - centerY;
        float resX = difX*cos(radAngle) - difY*sin(radAngle);
        float resY = difX*sin(radAngle) + difY*cos(radAngle);
        resX += centerX - baseX - partWidth/2;
        resY += centerY - baseY - width/2;

        SDL_SetTextureAlphaMod(texture, 0xFF * ((float)partTimes[i] / timeToFade));
        SDL_Rect clip_rect {(int)(clipX), 0, (int)(clipX + wDif), (int)(texture_h)};
        SDL_Rect render_rect {(int)(resX), (int)(resY), (int)(partWidth), (int)(width)};
        SDL_RenderCopyEx(renderer, texture, &clip_rect, &render_rect, centerRotation, NULL, SDL_FLIP_NONE);
        clipX = (int)(clipX + wDif) % (int)(patterns * wDif);
    }
    SDL_SetTextureAlphaMod(texture, 0xFF);
}

bool LightTrasser::update() {
    for (size_t i = 0; i < parts.size(); i++) {
        //SDL_Log("(%d: %f %f) ", partTimes[i], parts[i].first, parts[i].second);
        partTimes[i]--;
        if (partTimes[i] < 0) {
            partTimes.erase(partTimes.begin()+i);
            parts.erase(parts.begin()+i);
        }
    }
    if (parts.size() == 0)
        return false;

    float radRot = rotation/180*M_PI;
    if (target) {
        xEnd = target->getX();// - target->getWidth()/2*cos(radRot) + width/2*sin(radRot);
        yEnd = target->getY();// - target->getWidth()/2*sin(radRot) - width/2*cos(radRot);
    }
    timer++;
    //SDL_Log("%f %f", xEnd, yEnd);
    if (distance(xEnd, yEnd, (parts.end()-1)->first, (parts.end()-1)->second) >= (partWidth)) {
        partTimes.push_back(timeToFade);
        parts.push_back(std::pair<float, float>((parts.end()-1)->first + partWidth*cos(radRot), (parts.end()-1)->second + partWidth*sin(radRot)));
    }
    return true;
}
