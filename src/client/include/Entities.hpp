/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_ENTITIES_HPP_
#define SRC_CLIENT_INCLUDE_ENTITIES_HPP_

#include <math.h>
#include <vector>

#include "SDL.h"
#include "Equipment.hpp"

// 1st floor --------
class Entity {
 public:
    Entity(int x, int y): x(x), y(y) {}

    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void update() = 0;

    virtual ~Entity();

 protected:
    float x, y, rotation;
};

// 2nd floor --------
class Human: public Entity {
 public:
    Human(int x, int y, float _radius, float _speed):
        Entity(x, y), radius(_radius)), speed(_speed) {;}

    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void update() = 0;

    virtual ~Human();
 protected:
    float radius;
    float speed;
    vector<Equipment*> equipment;
};

class Technic: public Entity {
 public:
    Techinc(int x, int y, int _width, int _height, float _speed):
        Entity(x, y), width(_width), height(_height), speed(_speed) {;}

    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void update() = 0;

    virtual ~Technic();

 protected:
    int width, height;
    float speed;
    const int capacity;
};

class Object: public Entity {
 public:
    Object(int x, int y, int _width, int _height):
        Entity(x, y), width(_width), height(_height) {;}

    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void update() = 0;

    virtual ~Object();
 protected:
    int width, height;
};

// 3rd floor --------
class Player: public Human {
 public:
    Player(int x, int y, float _radius, float _speed):
        Human(x, y, _radius, _speed) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

 protected:

};

class Bot: public Human {
 public:
    Bot(int x, int y, float _radius, float _speed):
        Human(x, y, _radius, _speed) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

 protected:
    float speed;
};


class Tank: public Technic {
 public:
    Tank(int x, int y, int _width, int _height, float _speed):
        Techinc(x, y, _width, _height, _speed): {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

 protected:

};

class Machine: public Technic {
 public:
    Machine(int x, int y, int _width, int _height, float _speed):
        Techinc(x, y, _width, _height, _speed): {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

 protected:

};

class Copter: public Technic {
 public:
    Copter(int x, int y, int _width, int _height, float _speed):
        Techinc(x, y, _width, _height, _speed): {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

 protected:

};


class Box: public Object {
 public:
    Box(int x, int y, int _width, int _height):
        Object(x, y, _width, _height) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

 protected:

};

class Tree: public Object {
 public:
    Tree(int x, int y, int _width, int _height):
        Object(x, y, _width, _height) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

 protected:

};

class House: public Object {
 public:
    House(int x, int y, int _width, int _height):
        Object(x, y, _width, _height) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

 protected:

};

#endif  // SRC_CLIENT_INCLUDE_ENTITIES_HPP_
