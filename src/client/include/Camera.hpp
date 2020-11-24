/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_CAMERA_HPP_
#define SRC_CLIENT_INCLUDE_CAMERA_HPP_

#include "SDL.h"
#include "Entities.hpp"
#include "World.hpp"

class Camera {
 public:
    Camera(float _x, float _y, float _z, float _angle, float _width, float _height, float _rotation, World* _world, Entity* _target = NULL, bool _seek_rotation = false):
        x(_x), y(_y), z(_z), angle(_angle), width(_width), height(_height), rotation(_rotation), world(_world), target(_target), seek_rotation(_seek_rotation) {;}
    ~Camera();

    void render(SDL_Renderer *renderer);
    void update();

    void changeSize(float multiplier) {width *= multiplier; height *= multiplier;}
    void changeSize(float _width, float _height) {width = _width; height = _height;}
    void setTarget(Entity* _target = NULL) {target = _target;}

 private:
    float x, y, z, angle, rotation, width, height;
    Entity* target;
    World* world;
    bool seek_rotation;
};

#endif  // SRC_CLIENT_INCLUDE_CAMERA_HPP_
