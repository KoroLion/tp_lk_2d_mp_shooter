#include "Player.hpp"

Player::Player(){

}
Player::~Player(){

}

void Player::update(unsigned int _time) override{

}
int Player::getType() override {
}

int Player::getRadius(){
    return this->radius;
}
int Player::getAngle(){
    return this->angle;
}
unsigned int Player::getSpeed(){
    return this->speed;
}
unsigned int Player::getHp(){
    return this->hp;
}
unsigned int Player::getDamage(){
    return this->damage;
}

void Player::setRadius(int _radius){
    this->radius = _radius;
}
void Player::setAngle(int _angle){
    this->angle = _angle;
}
void Player::setSpeed(unsigned int _speed){
    this->speed = _speed;
}
void Player::setHp(unsigned int _hp){
    this->hp = _hp;
}
void Player::setDamage(unsigned int _damage){
    this->damage = _damage;
}