/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_ENTITIES_HPP_
#define SRC_CLIENT_INCLUDE_ENTITIES_HPP_

#include <vector>

class Entity;

#include "SDL.h"
#include "Equipments.hpp"
#include "World.hpp"

float getAngle(float centerX, float centerY, float x, float y);
float distance(float x1, float y1, float x2, float y2);

// 1st floor --------
class Entity {
 public:
    Entity(float _x, float _y, float _z, float _width, float _height, float _rotation, SDL_Texture* _texture):
        x(_x), y(_y), z(_z), width(_width), height(_height), rotation(_rotation), texture(_texture) {;}

    virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angleX);
    virtual bool update() {return true;}
    void updateToTarget(Entity* lastTarget, Entity* target, float percentage);

    virtual void moveAbsolute(float toForward, float toSide, float absoluteAngle = 0);
    void rotateRelative(float addRotation) {rotation += addRotation;}

    float getX() {return x;}
    float getY() {return y;}
    float getWidth() {return width;}
    float getHeight() {return height;}
    float getRotation() {return rotation;}
    void setRotation(float _rotation) {rotation = _rotation;}

    virtual ~Entity() {;}

 protected:
    float x, y, z, width, height, rotation, hp;
    SDL_Texture *texture;
};

// 2nd floor --------
class Player: public Entity {
 public:
    Player(float _x, float _y, float _z, float _width, float _height, float _rotation, SDL_Texture* _texture, float _speed):
        Entity(_x, _y, _z, _width, _height, _rotation, _texture), speed(_speed), bulletsOnMap(0) {
    }

    virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angleX);
    //virtual bool update();

    void moveRelative(float addAngle);
    virtual void shoot(World* world, SDL_Texture* bullet_texture, SDL_Texture* trasser_texture, SDL_Texture* small_trasser_texture);

    float getSpeed() {return speed;}

    ~Player() {;}
 protected:
    float speed;
    int bulletsOnMap;
    std::vector<Equipment*> equipment;
};

class Bullet: public Entity {
 public:
    Bullet(float _x, float _y, float _z, float _width, float _height, float _rotation, SDL_Texture* _texture, float _speed):
        Entity(_x, _y, _z, _width, _height, _rotation, _texture), speed(_speed) {
    }

    void moveRelative(float addAngle);

    virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angleX);
    virtual bool update();

    virtual ~Bullet() {;}

 protected:
    float speed;
    const float acceleration = 0.1;
    const float minSpeed = 5;
};

class Technic: public Entity {
 public:
    Technic(float _x, float _y, float _z, float _width, float _height, float _rotation, SDL_Texture* _texture, float _speed, int _capacity):
        Entity(_x, _y, _z, _width, _height, _rotation, _texture), speed(_speed), capacity(_capacity) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

    virtual ~Technic() {;}

 protected:
    float speed;
    const int capacity;
};

class Object: public Entity {
 public:
    Object(float _x, float _y, float _z, float _width, float _height, float _rotation, SDL_Texture* _texture):
        Entity(_x, _y, _z, _width, _height, _rotation, _texture) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

    virtual ~Object() {;}

 protected:
};

// 3rd floor --------
class Tank: public Technic {
 public:
    Tank(float _x, float _y, float _z, float _width, float _height, float _rotation, float _speed, SDL_Texture* _texture):
        Technic(_x, _y, _z, _width, _height, _rotation, _texture, _speed, 1) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};

class Machine: public Technic {
 public:
    Machine(float _x, float _y, float _z, float _width, float _height, float _rotation, float _speed, SDL_Texture* _texture):
        Technic(_x, _y, _z, _width, _height, _rotation, _texture, _speed, 3) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};

class Copter: public Technic {
 public:
    Copter(float _x, float _y, float _z, float _width, float _height, float _rotation, float _speed, SDL_Texture* _texture):
        Technic(_x, _y, _z, _width, _height, _rotation, _texture, _speed, 2) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};


class Obstacle: public Object {
 public:
    Obstacle(float _x, float _y, float _z, float _width, float _height, float _rotation, SDL_Texture* _texture):
        Object(_x, _y, _z, _width, _height, _rotation, _texture) {;}

    ////virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

    virtual ~Obstacle() {;}
 protected:

};

class Tree: public Object {
 public:
    Tree(float _x, float _y, float _z, float _width, float _height, float _rotation, SDL_Texture* _texture):
        Object(_x, _y, _z, _width, _height, _rotation, _texture) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};

class House: public Object {
 public:
    House(float _x, float _y, float _z, float _width, float _height, float _rotation, SDL_Texture* _texture):
        Object(_x, _y, _z, _width, _height, _rotation, _texture) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};

#endif  // SRC_CLIENT_INCLUDE_ENTITIES_HPP_
