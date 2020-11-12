#include "GameObject.hpp"

GameObject::GameObject(){

}

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

unsigned int GameObject::getTime(){
    return this->timeModified;
}

void GameObject::setTime(unsigned int _time){
    this->timeModified = _time;
}

MoveDirection GameObject::getDirection(){
    return this->direction;
}

void GameObject::setDirection(MoveDirection _direction){
    this->direction = direction;
}