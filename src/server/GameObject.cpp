#include "GameObject.hpp"

GameObject::GameObject(unsigned int _id,
                       Coordinates _coord,
                       Type _type,
                       std::chrono::time_point<std::chrono::steady_clock> _time,
                       MoveDirection _direction,
                       float _angle,
                       float _hp,
                       float _width,
                       float _height) :
    id(_id),
    coordinates(_coord),
    previousCoordinates(_coord),
    type(_type),
    timeModified(_time),
    direction(_direction),
    angle(_angle),
    hp(_hp),
    width(_width),
    height(_height) {}

GameObject::~GameObject() {}

unsigned int GameObject::getId(){
    return this->id;
}

void GameObject::setId(unsigned int _id){
    this->id = _id;
}

Coordinates GameObject::getCoordinates(){
    return this->coordinates;
}

void GameObject::setCoordinates(Coordinates _coordinates){
    this->coordinates = _coordinates;
}

std::chrono::time_point<std::chrono::steady_clock> GameObject::getTime(){
    return this->timeModified;
}

void GameObject::setTime(std::chrono::time_point<std::chrono::steady_clock> _time){
    this->timeModified = _time;
}

MoveDirection GameObject::getDirection(){
    return this->direction;
}

void GameObject::setDirection(MoveDirection _direction){
    this->direction = _direction;
}


float GameObject::getAngle(){
    return this->angle;
}


void GameObject::setAngle(float _angle){
    this->angle = _angle;
}

void GameObject::setHp(float _hp){
    this->hp = _hp;
}

float GameObject::getHp(){
    return this->hp;
}

void GameObject::reduceHp(float _damage) {
    this->hp -= _damage;
    if (this->hp < 0)
        this->hp = 0;
}

bool GameObject::update(std::chrono::time_point<std::chrono::steady_clock> _time) {
    previousCoordinates = coordinates;
    return true;
}

void GameObject::reverseUpdate() {
    coordinates = previousCoordinates;
}

float GameObject::getWidth(){
    return this->width;
}
float GameObject::getHeight(){
    return this->height;
}

void GameObject::setWidth(float _width){
    this->width = _width;
}
void GameObject::setHeight(float _height){
    this->height = _height;
}

float GameObject::getDamage() {
        return 0;
}

void GameObject::reload(unsigned int _bullets) {
}
bool GameObject::shoot() {
    return false;
}

Coordinates GameObject::minCoord() {
    return Coordinates(this->coordinates.x - (width / 2), this->coordinates.y - (height / 2));
}

Coordinates GameObject::maxCoord() {
    return Coordinates(this->coordinates.x + (width / 2), this->coordinates.y + (height / 2));
}

float GameObject::getX() {
    return this->coordinates.x;
}

float GameObject::getY() {
    return this->coordinates.y;
}

unsigned int GameObject::getOwner() {
    return this->id;
}