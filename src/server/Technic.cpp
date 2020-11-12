#include "Technic.hpp"

Technic::Technic(){

}
Technic::~Technic(){

}

void Technic::update(unsigned int _time) override{

}
int Technic::getType() override {

}

unsigned int Technic::getWidth(){
    return this->width;
}
unsigned int Technic::getHeight(){
    return this->height;
}
int Technic::getAngle(){
    return this->angle;
}
unsigned int Technic::getSpeed(){
    return this->speed;
}
unsigned int Technic::getHp(){
    return this->hp;
}
unsigned int Technic::getDamage(){
    return this->damage;
}

void Technic::setWidth(unsigned int _width){
    this->width = _width;
}
void Technic::setHeight(unsigned int _height){
    this->height = _height;
}
void Technic::setAngle(int _angle){
    this->angle = _angle;
}
void Technic::setSpeed(unsigned int _speed){
    this->speed = _speed;
}
void Technic::setHp(unsigned int _hp){
    this->hp = _hp
}
void Technic::setDamage(unsigned int _damage){
    this->damage = _damage;
}