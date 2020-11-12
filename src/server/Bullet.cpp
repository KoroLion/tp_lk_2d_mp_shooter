#include "Bullet.h"

Bullet::Bullet() {

}

Bullet::~Bullet() {

}

void Bullet::Update(unsigned int _time) override{

}

int Bullet::GetType() override{

}

int Bullet::GetAngle(){
    return this->angle;
}

unsigned int Bullet::GetSpeed(){
    return this->speed;
}

unsigned int Bullet::GetDamage(){
    return this->damage;
}

void Bullet::SetAngle(int _angle){
    this->angle = _angle;
}
void Bullet::SetSpeed(unsigned int _speed){
    this->speed = _speed;
}

void Bullet::SetDamage(unsigned int _damage){
    this->damage = _damage;
}
