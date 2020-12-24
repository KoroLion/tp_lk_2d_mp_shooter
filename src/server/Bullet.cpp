#include "Bullet.hpp"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

Bullet::Bullet(unsigned int _id,
               Coordinates _coord,
               Type _type,
               std::chrono::time_point<std::chrono::steady_clock> _time,
               float _angle,
               float _hp,
               float _width,
               float _height,
               unsigned int _owner,
               float _speed,
               float _damage,
               float _acceleration,
               float _minSpeed) : GameObject(_id, _coord, _type, _time, _angle, _hp, _width, _height) {
    this->owner = _owner;
    this->damage = _damage;
    this->acceleration = _acceleration;
    this->minSpeed = _minSpeed;
    this->speed = _speed;
}

Bullet::~Bullet() {}

bool Bullet::update(std::chrono::time_point<std::chrono::steady_clock> _time) {
    std::chrono::duration<float> deltaTime = _time - this->getTime();
    this->setTime(_time);
    if (!this->isMoving())
        return true;
    GameObject::update(_time);
    this->speed -= this->acceleration;
    if (speed < minSpeed)
        return false;
    float deltaCoord = deltaTime.count() * this->speed;
    float curAngle = this->getAngle();
    Coordinates coord = this->getCoordinates();
    coord.x += deltaCoord * std::cos(curAngle/180 * M_PI);
    coord.y += deltaCoord * std::sin(curAngle/180 * M_PI);
    this->setCoordinates(coord);
    return true;
}

Type Bullet::getType() const {
    return BULLET;
}

void Bullet::reverseUpdate() {
    return;
}

float Bullet::getDamage() const {
    return this->damage;
}

unsigned int Bullet::getOwner() const{
    return this->owner;
}

float Bullet::getHp() {
    return 0;
}

bool Bullet::isMoving() const {
    return true;
}