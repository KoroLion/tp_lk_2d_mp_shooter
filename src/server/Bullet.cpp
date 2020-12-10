#include "Bullet.hpp"

Bullet::Bullet(unsigned int _id,
               Coordinates _coord,
               Type _type,
               std::chrono::time_point<std::chrono::steady_clock> _time,
               MoveDirection _direction,
               float _angle,
               float _hp,
               float _width,
               float _height,
               float _damage,
               float _acceleration,
               float _minSpeed) : GameObject(_id, _coord, _type, _time, _direction, _angle, _hp, _width, _height) {
    this->damage = _damage;
    this->acceleration = _acceleration;
    this->minSpeed = _minSpeed;
    this->speed = _minSpeed;
}

Bullet::~Bullet() {}

void Bullet::update(std::chrono::time_point<std::chrono::steady_clock> _time) {
    std::chrono::duration<float> deltaTime = _time - this->getTime();
    this->setTime(_time);
    if (this->getDirection() == NO_MOVE)
        return;
    GameObject::update(_time);
    this->speed += this->acceleration * deltaTime.count();
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

Type Bullet::getType() {
    return BULLET;
}

void Bullet::reverseUpdate() {
    return;
}

float Bullet::getDamage() {
    return this->damage;
}