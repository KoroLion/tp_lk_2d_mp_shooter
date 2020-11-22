/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include <iostream>
#include <math.h>

#include "SDL.h"
#include "include/Entities.hpp"

float getAngle(float centerX, float centerY, float x, float y) {
    if (x - centerX == 0)
        if (y > centerY)
            return 90;
        else
            return -90;
    else
        if (x < centerX)
            return atan((float)(y - centerY) / (float)(x - centerX)) / M_PI*180 + 180;
        else
            return atan((float)(y - centerY) / (float)(x - centerX)) / M_PI*180;
}

void drawPoint(SDL_Renderer* renderer, int x, int y, int width, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect render_rect {x-width/2, y-width/2, width, width};
    SDL_RenderFillRect(renderer, &render_rect);
}

/*
void renderAsTrapeze(SDL_Renderer *renderer, SDL_Texture* texture, float anchorX, float anchorY, float width, float height,
                     float finalRotation, float leftRotation, float RightRotation, float patterns) {
    int texture_w, texture_h;
    SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h);
    float wDif = texture_w / patterns;
    float screenWidthDif = width / patterns;
    float angle = finalRotation + leftRotation;
    float angleDif = (RightRotation - leftRotation) / patterns;
    for (float clipX = 0; clipX < texture_w; clipX += wDif) {
        SDL_Rect clip_rect {(int)(clipX), 0, (int)(wDif), (int)(texture_h)};
        SDL_Point rotatePoint {(int)(screenWidthDif/2), 0};
        SDL_Rect render_rect {(int)(anchorX), (int)(anchorY), (int)(screenWidthDif / cos(angle /180*M_PI)), (int)(height / cos(angle /180*M_PI))};
        SDL_RenderCopyEx(renderer, texture, &clip_rect, &render_rect, angle, &rotatePoint, SDL_FLIP_NONE);
        angle += angleDif;
        anchorX += screenWidthDif;
    }

    //SDL_Rect render_rect {(int)(anchorX), (int)(anchorY), (int)(width), (int)(height)};
    //SDL_RenderCopyEx(renderer, texture, NULL, &render_rect, finalRotation, p_rotatePoint, SDL_FLIP_NONE);
    drawPoint(renderer, anchorX, anchorY);
}
*/
void renderAsHorizontalTrapeze(SDL_Renderer *renderer, SDL_Texture* texture, float anchorX, float anchorY, float width, float height,
                     float rotation, float leftRotation, float rightRotation, float patterns, float altitude) {
    int texture_w, texture_h;
    SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h);
    float hDif = texture_h / patterns;

    float leftLen = altitude; //height / cos((leftRotation-rotation) /180*M_PI);
    float perp = leftLen * cos((leftRotation-rotation) /180*M_PI);
    float leftYDif = leftLen * cos(leftRotation /180*M_PI) / patterns;
    float leftXDif = leftYDif * tan(leftRotation /180*M_PI);

    float widthDif = (perp * tan((leftRotation-rotation) /180*M_PI) - perp * tan((rightRotation-rotation) /180*M_PI)) / patterns;

    for (float clipY = 0; clipY < texture_h; clipY += hDif) {
        SDL_Rect clip_rect {0, (int)(clipY), (int)(texture_w), (int)(clipY + hDif)};
        //drawPoint(renderer, anchorX, anchorY, 5, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_Point rotatePoint {0, 0};
        SDL_Rect render_rect {(int)(anchorX), (int)(anchorY), (int)(width), (int)(perp/patterns+2)};
        SDL_RenderCopyEx(renderer, texture, &clip_rect, &render_rect, rotation, &rotatePoint, SDL_FLIP_NONE);
        width += widthDif;
        anchorY += leftYDif;
        anchorX -= leftXDif;
    }
    //drawPoint(renderer, anchorX, anchorY, 3);
}

void renderAsVerticalTrapeze(SDL_Renderer *renderer, SDL_Texture* texture, float anchorX, float anchorY, float width, float height,
                     float rotation, float leftRotation, float rightRotation, float patterns, float altitude) {
    int texture_w, texture_h;
    SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h);
    float wDif = texture_w / patterns;

    float leftLen = altitude; //width / cos((leftRotation-rotation) /180*M_PI);
    float perp = leftLen * cos((leftRotation-rotation) /180*M_PI);
    float leftXDif = leftLen * cos(leftRotation /180*M_PI) / patterns;
    float leftYDif = leftXDif * tan(leftRotation /180*M_PI);

    float heightDif = (-perp * tan((leftRotation-rotation) /180*M_PI) + perp * tan((rightRotation-rotation) /180*M_PI)) / patterns;

    for (float clipX = 0; clipX < texture_w; clipX += wDif) {
        SDL_Rect clip_rect {(int)(clipX), 0, (int)(clipX + wDif), (int)(texture_h)};
        //drawPoint(renderer, anchorX, anchorY, 5, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_Point rotatePoint {0, 0};
        SDL_Rect render_rect {(int)(anchorX), (int)(anchorY), (int)(perp/patterns+2), (int)(height)};
        SDL_RenderCopyEx(renderer, texture, &clip_rect, &render_rect, rotation, &rotatePoint, SDL_FLIP_NONE);
        height += heightDif;
        anchorY += leftYDif;
        anchorX += leftXDif;
    }
    //drawPoint(renderer, anchorX, anchorY, 3);
}

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

    float radRot = (rotation - centerRotation)/180*M_PI;
    SDL_Rect render_rect {(int)(resX - baseX), (int)(resY - baseY), (int)width, (int)height};
    SDL_RenderCopyEx(renderer, texture, NULL, &render_rect, rotation - centerRotation, NULL, SDL_FLIP_NONE);

    renderAsHorizontalTrapeze(renderer, texture, resX+width/2 - ((width/2)*cos(radRot) - height/2*sin(radRot)) - baseX, resY+height/2 - ((width/2)*sin(radRot) + height/2*cos(radRot)) - baseY,
                    width, height, rotation - centerRotation,
                    -90 + getAngle(centerX - baseX, centerY - baseY, resX+width/2 - baseX - ((width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY - ((width/2)*sin(radRot) + height/2*cos(radRot))),
                    -90 + getAngle(centerX - baseX, centerY - baseY, resX+width/2 - baseX - (-(width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY - (-(width/2)*sin(radRot) + height/2*cos(radRot))),
                    width/1, 50);
    renderAsHorizontalTrapeze(renderer, texture, resX+width/2 + ((width/2)*cos(radRot) - (height/2)*sin(radRot)) - baseX, resY+height/2 + ((width/2)*sin(radRot) + (height/2)*cos(radRot)) - baseY,
                    width, height, rotation - centerRotation + 180,
                    -90 + getAngle(centerX - baseX, centerY - baseY, resX+width/2 - baseX + ((width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY + ((width/2)*sin(radRot) + height/2*cos(radRot))),
                    -90 + getAngle(centerX - baseX, centerY - baseY, resX+width/2 - baseX + (-(width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY + (-(width/2)*sin(radRot) + height/2*cos(radRot))),
                    width/1, 50);

    renderAsVerticalTrapeze(renderer, texture, resX+width/2 - ((width/2)*cos(radRot) - height/2*sin(radRot)) - baseX, resY+height/2 - ((width/2)*sin(radRot) + height/2*cos(radRot)) - baseY,
                    width, height, rotation - centerRotation,
                    getAngle(centerX - baseX, centerY - baseY, resX+width/2 - baseX - ((width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY - ((width/2)*sin(radRot) + height/2*cos(radRot))),
                    getAngle(centerX - baseX, centerY - baseY, resX+width/2 - baseX + (-(width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY + (-(width/2)*sin(radRot) + height/2*cos(radRot))),
                    width/1, 50);
    renderAsVerticalTrapeze(renderer, texture, resX+width/2 + ((width/2)*cos(radRot) - height/2*sin(radRot)) - baseX, resY+height/2 + ((width/2)*sin(radRot) + height/2*cos(radRot)) - baseY,
                    width, height, rotation - centerRotation + 180,
                    getAngle(centerX - baseX, centerY - baseY, resX+width/2 - baseX + ((width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY + ((width/2)*sin(radRot) + height/2*cos(radRot))),
                    getAngle(centerX - baseX, centerY - baseY, resX+width/2 - baseX - (-(width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY - (-(width/2)*sin(radRot) + height/2*cos(radRot))),
                    width/1, 50);
    drawPoint(renderer, centerX - baseX, centerY - baseY, 5, 0x00, 0x00, 0xFF, 0xFF);
    //drawPoint(renderer, resX+width/2 - baseX - ((width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY - ((width/2)*sin(radRot) + height/2*cos(radRot)), 5, 0xFF, 0x00, 0x00, 0xFF);
    //drawPoint(renderer, resX+width/2 - baseX - ((width/2)*cos(radRot) - height/2*sin(radRot)), resY+height/2 - baseY - ((width/2)*sin(radRot) + height/2*cos(radRot)), 5, 0x00, 0xFF, 0x00, 0xFF);
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

void Entity::moveAbsolute(float toForward, float toSide, float absoluteAngle) {
    x += toForward * cos(absoluteAngle/180*M_PI);
    y += toForward * sin(absoluteAngle/180*M_PI);
    x += toSide * sin(absoluteAngle/180*M_PI);
    y += toSide * cos(absoluteAngle/180*M_PI);
}

void Player::moveRelative(float addAngle) {
    x += speed * cos((addAngle + rotation)/180*M_PI);
    y += speed * sin((addAngle + rotation)/180*M_PI);
}
