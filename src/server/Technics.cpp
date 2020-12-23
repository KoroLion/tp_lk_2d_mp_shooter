#include "Technics.hpp"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

Technics::Technics(unsigned int _id,
                   Coordinates _coord,
                   Type _type,
                   std::chrono::time_point<std::chrono::steady_clock> _time,
                   float _angle,
                   float _hp,
                   float _width,
                   float _height,
                   float _speed,
                   unsigned int _capacity) :
                   GameObject(_id, _coord, _type, _time, _angle, _hp, _width, _height) {

    this->speed = _speed;
    this->capacity = _capacity;
}

Technics::~Technics(){}

bool Technics::update(std::chrono::time_point<std::chrono::steady_clock> _time) {
    std::chrono::duration<float> deltaTime = _time - this->getTime();
    this->setTime(_time);
    if (!this->isMoving())
        return true;
    GameObject::update(_time);
    float deltaCoord = deltaTime.count() * this->speed;
    float curAngle = this->getAngle();
        Coordinates coord = this->getCoordinates();
        coord.x += deltaCoord * std::cos(curAngle/180 * M_PI);
        coord.y += deltaCoord * std::sin(curAngle/180 * M_PI);
    this->setCoordinates(coord);
    return true;
}

Type Technics::getType() const{
    return TECHNICS;
}

