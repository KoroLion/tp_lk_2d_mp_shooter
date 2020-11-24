/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#include <iostream>
#include <math.h>

#include "SDL.h"
#include "include/Entities.hpp"
#include "include/Colors.hpp"


bool isIntersect (float x11,float y11, float x12,float y12, float x21,float y21, float x22,float y22) {
    float x1 = x12-x11;
    float y1 = y12-y11;
    float x2 = x21-x22;
    float y2 = y21-y22;
    //считаем уравнения прямых проходящих через отрезки
    float a1 = -y1;
    float b1 = +x1;
    float d1 = -(a1*x11 + b1*y11);

    float a2 = -y2;
    float b2 = +x2;
    float d2 = -(a2*x21 + b2*y21);

    //подставляем концы отрезков, для выяснения в каких полуплоскотях они
    float seg1_line2_start = a2*x11 + b2*y11 + d2;
    float seg1_line2_end = a2*x12 + b2*y12 + d2;

    float seg2_line1_start = a1*x21 + b1*y21 + d1;
    float seg2_line1_end = a1*x22 + b1*y22 + d1;

    //если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
    if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0)
        return false;
    return true;
}

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

float distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

void drawPoint(SDL_Renderer* renderer, int x, int y, int width, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect render_rect {x-width/2, y-width/2, width, width};
    SDL_RenderFillRect(renderer, &render_rect);
}

void drawLine(SDL_Renderer* renderer, float x1, float y1, float x2, float y2, int width, int r, int g, int b, int a) {
    float patterns = distance(x1,y1, x2,y2)/width;
    float xDif = (x2-x1) / patterns;
    float yDif = (y2-y1) / patterns;
    for (int i = 0; i < patterns; i++)
        drawPoint(renderer, x1 += xDif, y1 += yDif, width, r,g,b,a);
}


/*void renderAsHorizontalTrapeze(SDL_Renderer *renderer, SDL_Texture* texture, float anchorX, float anchorY, float width, float height,
                                 float finalRotation, float leftRotation, float RightRotation, float patterns, float altitude) {
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
}*/
void renderAsHorizontalTrapeze(SDL_Renderer *renderer, SDL_Texture* texture, float anchorX, float anchorY, float width, float height,
                               float rotation, float leftRotation, float rightRotation, float patterns) {
    int texture_w, texture_h;
    SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h);
    float hDif = texture_h / patterns;

    float leftLen = height; //height / cos((leftRotation-rotation) /180*M_PI);
    float trapezeHeight = leftLen * cos((leftRotation-rotation) /180*M_PI);
    float leftYDif = leftLen * cos(leftRotation /180*M_PI) / patterns;
    float leftXDif = leftYDif * tan(leftRotation /180*M_PI);

    float widthDif = (trapezeHeight * tan((leftRotation-rotation) /180*M_PI) - trapezeHeight * tan((rightRotation-rotation) /180*M_PI)) / patterns;
    float heightDif = trapezeHeight/patterns+2;

    SDL_Point rotatePoint {0, 0};
    for (float clipY = 0; clipY < texture_h; clipY += hDif) {
        SDL_Rect clip_rect {0, (int)(clipY), (int)(texture_w), (int)(clipY + hDif)};
        //drawPoint(renderer, anchorX, anchorY, 5, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_Rect render_rect {(int)(anchorX), (int)(anchorY), (int)(width), (int)(heightDif)};
        SDL_RenderCopyEx(renderer, texture, &clip_rect, &render_rect, rotation, &rotatePoint, SDL_FLIP_NONE);
        width += widthDif;
        anchorY += leftYDif;
        anchorX -= leftXDif;
    }
    //drawPoint(renderer, anchorX, anchorY, 3);
}

void renderAsVerticalTrapeze(SDL_Renderer *renderer, SDL_Texture* texture, float anchorX, float anchorY, float height, float width,
                             float rotation, float leftRotation, float rightRotation, float patterns) {
    int texture_w, texture_h;
    SDL_QueryTexture(texture, NULL, NULL, &texture_w, &texture_h);
    float wDif = texture_w / patterns;

    float leftLen = width; //width / cos((leftRotation-rotation) /180*M_PI);
    float trapezeHeight = leftLen * cos((leftRotation-rotation) /180*M_PI);
    float leftXDif = leftLen * cos(leftRotation /180*M_PI) / patterns;
    float leftYDif = leftXDif * tan(leftRotation /180*M_PI);

    float heightDif = (-trapezeHeight * tan((leftRotation-rotation) /180*M_PI) + trapezeHeight * tan((rightRotation-rotation) /180*M_PI)) / patterns;
    float widthDif = trapezeHeight/patterns+2;

    SDL_Point rotatePoint {0, 0};
    for (float clipX = 0; clipX < texture_w; clipX += wDif) {
        SDL_Rect clip_rect {(int)(clipX), 0, (int)(clipX + wDif), (int)(texture_h)};
        //drawPoint(renderer, anchorX, anchorY, 5, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_Rect render_rect {(int)(anchorX), (int)(anchorY), (int)(widthDif), (int)(height)};
        SDL_RenderCopyEx(renderer, texture, &clip_rect, &render_rect, rotation, &rotatePoint, SDL_FLIP_NONE);
        height += heightDif;
        anchorY += leftYDif;
        anchorX += leftXDif;
    }
    //drawPoint(renderer, anchorX, anchorY, 3);
}

void Entity::render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angleX) {
    if (texture == NULL)
        return;
    float radAngle = -centerRotation/180*M_PI;
    float difX = x - centerX;
    float difY = y - centerY;
    float resX = difX*cos(radAngle) - difY*sin(radAngle);
    float resY = difX*sin(radAngle) + difY*cos(radAngle);
    centerX -= baseX;
    centerY -= baseY;
    resX += centerX;
    resY += centerY;

    centerRotation = rotation - centerRotation; // now it's absolute rotation

    SDL_Rect render_rect {(int)(resX - width/2), (int)(resY - height/2), (int)(width), (int)(height)};
    SDL_RenderCopyEx(renderer, texture, NULL, &render_rect, centerRotation, NULL, SDL_FLIP_NONE);

    float cosRot = cos(centerRotation/180*M_PI);
    float sinRot = sin(centerRotation/180*M_PI);

    float xLeftUp =    resX - ( width/2*cosRot - height/2*sinRot);
    float yLeftUp =    resY - ( width/2*sinRot + height/2*cosRot);
    float xRightUp =   resX - (-width/2*cosRot - height/2*sinRot);
    float yRightUp =   resY - (-width/2*sinRot + height/2*cosRot);
    float xLeftDown =  resX + (-width/2*cosRot - height/2*sinRot);
    float yLeftDown =  resY + (-width/2*sinRot + height/2*cosRot);
    float xRightDown = resX + ( width/2*cosRot - height/2*sinRot);
    float yRightDown = resY + ( width/2*sinRot + height/2*cosRot);

    //float angleY = angleX * (width/height);
    float k_3D = 1/(altitude-z)*altitude;
    float trapezeHeight = distance(xLeftUp-centerX,yLeftUp-centerY, (xLeftUp-centerX)*k_3D,(yLeftUp-centerY)*k_3D);
    float accuracy = trapezeHeight/4;
    if (!isIntersect(xLeftUp,yLeftUp,   centerX,centerY,  xLeftDown,yLeftDown, xRightUp,yRightUp) && // up
        !isIntersect(xRightUp,yRightUp, centerX,centerY,  xLeftUp,yLeftUp, xRightDown,yRightDown))
        renderAsHorizontalTrapeze(renderer, texture, xLeftUp, yLeftUp, width, trapezeHeight, centerRotation,
                                  getAngle(centerX, centerY, xLeftUp, yLeftUp) - 90,
                                  getAngle(centerX, centerY, xRightUp, yRightUp) - 90, accuracy);
    if (!isIntersect(xLeftUp,yLeftUp,     centerX,centerY,  xLeftDown,yLeftDown, xRightUp,yRightUp) &&  // left
        !isIntersect(xLeftDown,yLeftDown, centerX,centerY,  xLeftUp,yLeftUp, xRightDown,yRightDown))
        renderAsVerticalTrapeze(renderer, texture, xLeftUp, yLeftUp, height, trapezeHeight, centerRotation,
                                getAngle(centerX, centerY, xLeftUp, yLeftUp),
                                getAngle(centerX, centerY, xLeftDown, yLeftDown), accuracy);

    trapezeHeight = distance(xRightDown-centerX,yRightDown-centerY, (xRightDown-centerX)*k_3D,(yRightDown-centerY)*k_3D);
    accuracy = trapezeHeight/4;
    if (!isIntersect(xRightDown,yRightDown, centerX,centerY,  xLeftDown,yLeftDown, xRightUp,yRightUp) && // down
        !isIntersect(xLeftDown,yLeftDown,   centerX,centerY,  xLeftUp,yLeftUp, xRightDown,yRightDown))
        renderAsHorizontalTrapeze(renderer, texture, xRightDown, yRightDown, width, trapezeHeight, centerRotation + 180,
                                  getAngle(centerX, centerY, xRightDown, yRightDown) - 90,
                                  getAngle(centerX, centerY, xLeftDown, yLeftDown) - 90, accuracy);
    if (!isIntersect(xRightDown,yRightDown, centerX,centerY,  xLeftDown,yLeftDown, xRightUp,yRightUp) && // right
        !isIntersect(xRightUp,yRightUp,     centerX,centerY,  xLeftUp,yLeftUp, xRightDown,yRightDown))
        renderAsVerticalTrapeze(renderer, texture, xRightDown, yRightDown, height, trapezeHeight, centerRotation + 180,
                                getAngle(centerX, centerY, xRightDown, yRightDown),
                                getAngle(centerX, centerY, xRightUp, yRightUp), accuracy);
    //SDL_Rect render_rect {(int)(resX - width/2), (int)(resY - height/2), (int)(width), (int)(height)};
    render_rect.w *= k_3D;
    render_rect.h *= k_3D;
    render_rect.x = centerX + (resX-centerX)*k_3D - render_rect.w/2;
    render_rect.y = centerY + (resY-centerY)*k_3D - render_rect.h/2;

    SDL_RenderCopyEx(renderer, texture, NULL, &render_rect, centerRotation, NULL, SDL_FLIP_NONE);
    //drawPoint(renderer, centerX, centerY, 5, BLUE_RGBA);
}

void Entity::updateToTarget(Entity* lastTarget, Entity* target, float percentage) {
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


void Player::render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angleX) {
    if (texture == NULL)
        return;
    float radAngle = -centerRotation/180*M_PI;
    float difX = x - centerX;
    float difY = y - centerY;
    float resX = difX*cos(radAngle) - difY*sin(radAngle);
    float resY = difX*sin(radAngle) + difY*cos(radAngle);
    centerX -= baseX;
    centerY -= baseY;
    resX += centerX;
    resY += centerY;

    centerRotation = rotation - centerRotation; // now it's absolute rotation

    SDL_Rect render_rect {(int)(resX - width/2), (int)(resY - height/2), (int)(width), (int)(height)};
    SDL_RenderCopyEx(renderer, texture, NULL, &render_rect, centerRotation, NULL, SDL_FLIP_NONE);
    drawPoint(renderer, centerX, centerY, 5, BLUE_RGBA);
}

void Player::moveRelative(float addAngle) {
    x += speed * cos((addAngle + rotation)/180*M_PI);
    y += speed * sin((addAngle + rotation)/180*M_PI);
}
