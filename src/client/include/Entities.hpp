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
void drawLine(SDL_Renderer* renderer, float x1, float y1, float x2, float y2, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// 1st floor --------
class Entity {
 public:
    Entity(float _x, float _y, float _z, float _width, float _height, float _rotation, float _hp, SDL_Texture* _texture):
        x(_x), y(_y), z(_z), width(_width), height(_height), rotation(_rotation), hp(_hp), texture(_texture),
        maxHp(100) {;}

    virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angleX);
    virtual bool update() {return false;}
    void updateToTarget(Entity* lastTarget, Entity* target, float percentage);

    virtual void moveAbsolute(float toForward, float toSide, float absoluteAngle = 0);
    void rotateRelative(float addRotation) {rotation += addRotation;}

    float getX() {return x;}
    float getY() {return y;}
    float getWidth() {return width;}
    float getHeight() {return height;}
    float getRotation() {return rotation;}
    float getHp() {return hp;}
    void setRotation(float _rotation) {rotation = _rotation;}

    virtual ~Entity() {;}

 protected:
    float x, y, z, width, height, rotation, hp;
    SDL_Texture *texture;
    const float maxHp;
};

// 2nd floor --------
class Player: public Entity {
 public:
    Player(float _x, float _y, float _z, float _width, float _height, float _rotation, float _hp, SDL_Texture* _texture, float _speed):
        Entity(_x, _y, _z, _width, _height, _rotation, _hp, _texture), speed(_speed),
        maxAmmo(10), ammo(0), bulletsOnMap(0), reloadingTime(3000), timeToReload(reloadingTime) {
    }

    virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY, float altitude, float angleX);
    //virtual bool update();

    void moveRelative(float addAngle);
    virtual void shoot(World* world, SDL_Texture* bullet_texture, SDL_Texture* trasser_texture, SDL_Texture* small_trasser_texture);
    void reduceAmmo(int val) {ammo -= val; if (ammo < 0) ammo = 0;}
    bool isReloaded() {return timeToReload <= 0;}
    void updateTime(float dTime);
    void startReload() {timeToReload = reloadingTime;}

    float getSpeed() {return speed;}
    int getAmmo() {return ammo;}

    ~Player() {;}
 protected:
    float speed;
    const int maxAmmo;
    int ammo;
    int bulletsOnMap;
    const float reloadingTime;
    float timeToReload;
    std::vector<Equipment*> equipments;
};

class Bullet: public Entity {
 public:
    Bullet(float _x, float _y, float _z, float _width, float _height, float _rotation, float _hp, SDL_Texture* _texture, float _speed):
        Entity(_x, _y, _z, _width, _height, _rotation, _hp, _texture), speed(_speed) {
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
    Technic(float _x, float _y, float _z, float _width, float _height, float _rotation, float _hp, SDL_Texture* _texture, float _speed, int _capacity):
        Entity(_x, _y, _z, _width, _height, _rotation, _hp, _texture), speed(_speed), capacity(_capacity) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

    virtual ~Technic() {;}

 protected:
    float speed;
    const int capacity;
};

class Object: public Entity {
 public:
    Object(float _x, float _y, float _z, float _width, float _height, float _rotation, float _hp, SDL_Texture* _texture):
        Entity(_x, _y, _z, _width, _height, _rotation, _hp, _texture) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

    virtual ~Object() {;}

 protected:
};

// 3rd floor --------
class Tank: public Technic {
 public:
    Tank(float _x, float _y, float _z, float _width, float _height, float _rotation, float _speed, float _hp, SDL_Texture* _texture):
        Technic(_x, _y, _z, _width, _height, _rotation, _hp, _texture, _speed, 1) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};

class Machine: public Technic {
 public:
    Machine(float _x, float _y, float _z, float _width, float _height, float _rotation, float _speed, float _hp, SDL_Texture* _texture):
        Technic(_x, _y, _z, _width, _height, _rotation, _hp, _texture, _speed, 3) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};

class Copter: public Technic {
 public:
    Copter(float _x, float _y, float _z, float _width, float _height, float _rotation, float _speed, float _hp, SDL_Texture* _texture):
        Technic(_x, _y, _z, _width, _height, _rotation, _hp, _texture, _speed, 2) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};


class Obstacle: public Object {
 public:
    Obstacle(float _x, float _y, float _z, float _width, float _height, float _rotation, float _hp, SDL_Texture* _texture):
        Object(_x, _y, _z, _width, _height, _rotation, _hp, _texture) {;}

    ////virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

    virtual ~Obstacle() {;}
 protected:

};

class Tree: public Object {
 public:
    Tree(float _x, float _y, float _z, float _width, float _height, float _rotation, float _hp, SDL_Texture* _texture):
        Object(_x, _y, _z, _width, _height, _rotation, _hp, _texture) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};

class House: public Object {
 public:
    House(float _x, float _y, float _z, float _width, float _height, float _rotation, float _hp, SDL_Texture* _texture):
        Object(_x, _y, _z, _width, _height, _rotation, _hp, _texture) {;}

    //virtual void render(SDL_Renderer *renderer, float baseX, float baseY, float centerRotation, float centerX, float centerY);
    //virtual int update();

 protected:

};

#endif  // SRC_CLIENT_INCLUDE_ENTITIES_HPP_
