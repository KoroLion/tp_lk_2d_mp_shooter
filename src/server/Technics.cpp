#include "Technics.hpp"


Technics::Technics(unsigned int _id,
                   Coordinates _coord,
                   Type _type,
                   std::chrono::time_point<std::chrono::steady_clock> _time,
                   MoveDirection _direction,
                   float _angle,
                   float _hp,
                   float _width,
                   float _height,
                   float _speed,
                   unsigned int _capacity) :
                   GameObject(_id, _coord, _type, _time, _direction, _angle, _hp, _width, _height) {

    this->speed = _speed;
    this->capacity = _capacity;
}

Technics::~Technics(){}

void Technics::update(std::chrono::time_point<std::chrono::steady_clock> _time) {
    std::chrono::duration<float> deltaTime = _time - this->getTime();
    this->setTime(_time);
    if (this->getDirection() == NO_MOVE)
        return;
    GameObject::update(_time);
    float deltaCoord = deltaTime.count() * this->speed;
    float curAngle = this->getAngle();
    switch (this->getDirection()) {
        case BACK :
            curAngle += 180;
            break;
        case RIGHT :
            curAngle += 90;
            break;
        case LEFT :
            curAngle -= 90;
            break;
    }
    Coordinates coord = this->getCoordinates();
    coord.x += deltaCoord * std::cos(curAngle);
    coord.y += deltaCoord * std::sin(curAngle);
    this->setCoordinates(coord);
}

Type Technics::getType() {
    return TECHNICS;
}

