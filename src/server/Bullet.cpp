#include "Bullet.hpp"

Bullet::Bullet() {
    this->damage = 0;
    this->speed = 0;
    this->angle = 0;
}
Bullet(int _angle, unsigned int _speed, unsigned int _damage){
    this->damage = _damage;
    this->speed = _speed;
    this->angle = _angle;
}

Bullet::~Bullet() {

}

void Bullet::update(unsigned int _time) override{

}

int Bullet::getType() override{

}

int Bullet::getAngle(){
    return this->angle;
}

unsigned int Bullet::getSpeed(){
    return this->speed;
}

unsigned int Bullet::getDamage(){
    return this->damage;
}

void Bullet::setAngle(int _angle){
    this->angle = _angle;
}
void Bullet::setSpeed(unsigned int _speed){
    this->speed = _speed;
}

void Bullet::setDamage(unsigned int _damage){
    this->damage = _damage;
}
