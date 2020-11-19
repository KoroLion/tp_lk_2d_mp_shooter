/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_ENTITIES_HPP_
#define SRC_CLIENT_INCLUDE_ENTITIES_HPP_

#include <vector>

#include "SDL.h"
#include "Equipments.hpp"

SDL_Texture* loadTexture(SDL_Texture* _texture);

// 1st floor --------
class Entity {
 public:
    Entity(float _x, float _y, float _width, float _height, float _rotation, SDL_Texture* _texture):
        x(_x), y(_y), width(_width), height(_height), rotation(_rotation), texture(_texture) {;}

    virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    virtual void update() {;}
    void updateToTarget(Entity* lastTarget, Entity* target, float percentage);

    void moveAngledAbsolute(float toForward, float toSide, float absoluteAngle = 0);
    void rotateRelative(float addRotation) {rotation += addRotation;}

    float getX() {return x;}
    float getY() {return y;}
    float getRotation() {return rotation;}
    void setRotation(float _rotation) {rotation = _rotation;}

    virtual ~Entity() {;}

 protected:
    float x, y, width, height, rotation, hp;
    SDL_Texture *texture;
};

// 2nd floor --------
class Player: public Entity {
 public:
    Player(float _x, float _y, float _width, float _height, float _rotation, SDL_Texture* _texture, float _speed):
        Entity(_x, _y, _width, _height, _rotation, _texture), speed(_speed) {
    }

    //virtual void render(SDL_Renderer *renderer);
    //virtual void update();

    void moveRelative(float addAngle);

    ~Player() {;}
 protected:
    float speed;
    std::vector<Equipment*> equipment;
};

class Technic: public Entity {
 public:
    Technic(float _x, float _y, float _width, float _height, float _rotation, SDL_Texture* _texture, float _speed, int _capacity):
        Entity(_x, _y, _width, _height, _rotation, _texture), speed(_speed), capacity(_capacity) {;}

    //virtual void render(SDL_Renderer *renderer);
    //virtual void update();

    virtual ~Technic() {;}

 protected:
    float speed;
    const int capacity;
};

class Object: public Entity {
 public:
    Object(float _x, float _y, float _width, float _height, float _rotation, SDL_Texture* _texture):
        Entity(_x, _y, _width, _height, _rotation, _texture) {;}

    //virtual void render(SDL_Renderer *renderer);
    //virtual void update();

    virtual ~Object() {;}

 protected:
};

// 3rd floor --------
class Tank: public Technic {
 public:
    Tank(float _x, float _y, float _width, float _height, float _rotation, float _speed, SDL_Texture* _texture):
        Technic(_x, _y, _width, _height, _rotation, _texture, _speed, 1) {;}

    //virtual void render(SDL_Renderer *renderer);
    //virtual void update();

 protected:

};

class Machine: public Technic {
 public:
    Machine(float _x, float _y, float _width, float _height, float _rotation, float _speed, SDL_Texture* _texture):
        Technic(_x, _y, _width, _height, _rotation, _texture, _speed, 3) {;}

    //virtual void render(SDL_Renderer *renderer);
    //virtual void update();

 protected:

};

class Copter: public Technic {
 public:
    Copter(float _x, float _y, float _width, float _height, float _rotation, float _speed, SDL_Texture* _texture):
        Technic(_x, _y, _width, _height, _rotation, _texture, _speed, 2) {;}

    //virtual void render(SDL_Renderer *renderer);
    //virtual void update();

 protected:

};


class Obstacle: public Object {
 public:
    Obstacle(float _x, float _y, float _width, float _height, float _rotation, SDL_Texture* _texture):
        Object(_x, _y, _width, _height, _rotation, _texture) {;}

    ////virtual void render(SDL_Renderer *renderer);
    //virtual void update();

    virtual ~Obstacle() {;}
 protected:

};

class Tree: public Object {
 public:
    Tree(float _x, float _y, float _width, float _height, float _rotation, SDL_Texture* _texture):
        Object(_x, _y, _width, _height, _rotation, _texture) {;}

    //virtual void render(SDL_Renderer *renderer);
    //virtual void update();

 protected:

};

class House: public Object {
 public:
    House(float _x, float _y, float _width, float _height, float _rotation, SDL_Texture* _texture):
        Object(_x, _y, _width, _height, _rotation, _texture) {;}

    //virtual void render(SDL_Renderer *renderer);
    //virtual void update();

 protected:

};

#endif  // SRC_CLIENT_INCLUDE_ENTITIES_HPP_
