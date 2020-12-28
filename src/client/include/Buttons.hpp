/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_BUTTONS_HPP_
#define SRC_CLIENT_INCLUDE_BUTTONS_HPP_

#include <functional>

#include "SDL.h"
#include "SDL_TTF.h"

enum conditions {
    UP,
    DOWN,
    ONMOVE
};

class Button {
 public:
    Button(int _x, int _y, int _width, int _height, int _rotation,
           SDL_Texture* _defaultTexture, SDL_Texture* _onMoveTexture, SDL_Texture* _onClickTexture,
           TTF_Font* _font, const char* _text, Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a, const std::function<void(void)> &_onClick):
           x(_x), y(_y), width(_width), height(_height), rotation(_rotation),
           defaultTexture(_defaultTexture), onMoveTexture(_onMoveTexture), onClickTexture(_onClickTexture),
           font(_font), text(_text), r(_r), g(_g), b(_b), a(_a), condition(UP), onClick(_onClick) {;}

    virtual bool isInside(int xc, int yc) = 0;
    virtual void render(SDL_Renderer *renderer);
    virtual void update(int xc, int yc, bool buttonPress);

    int getX() {return x;}
    int getY() {return y;}
    int getWidth() {return width;}
    int getHeight() {return height;}
    int getRotation() {return rotation;}

    virtual ~Button() {;}

 protected:
    int x, y, width, height, rotation;
    SDL_Texture *defaultTexture, *onMoveTexture, *onClickTexture;
    TTF_Font* font;
    const char* text;
    SDL_Color textColor;
    Uint8 r, g, b, a;
    int condition;

    const std::function<void(void)> onClick;
};

class CircleButton: public Button {
 public:
    CircleButton(int _x, int _y, int _radius, int _rotation,
           SDL_Texture* _defaultTexture, SDL_Texture* _onMoveTexture, SDL_Texture* _onClickTexture,
           TTF_Font* _font, const char* _text, Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a, const std::function<void(void)> &_onClick):
           Button(_x, _y, _radius*2, _radius*2, _rotation, _defaultTexture, _onMoveTexture, _onClickTexture,
                  _font, _text, _r, _g, _b, _a, _onClick), radius(_radius) {;}
    virtual bool isInside(int xc, int yc) {return ((xc - x)*(xc - x) + (yc - y)*(yc - y) <= radius*radius);}

    ~CircleButton() {;}

 protected:
    int radius;

    virtual void onClick() {;}
};

class RectangleButton: public Button {
 public:
    RectangleButton(int _x, int _y, int _width, int _height, int _rotation,
           SDL_Texture* _defaultTexture, SDL_Texture* _onMoveTexture, SDL_Texture* _onClickTexture,
           TTF_Font* _font, const char* _text, Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a, const std::function<void(void)> &_onClick):
           Button(_x, _y, _width, _height, _rotation, _defaultTexture, _onMoveTexture, _onClickTexture,
                  _font, _text, _r, _g, _b, _a, _onClick) {;}
    virtual bool isInside(int xc, int yc) {return xc >= x-width/2 && xc <= x+width/2 && yc >= y-height/2 && yc <= y+height/2;}

    ~RectangleButton() {;}

 protected:
    virtual void onClick() {;}
};
#endif // SRC_CLIENT_INCLUDE_BUTTONS_HPP_
