#include "Obstacle.hpp"

Obstacle::Obstacle(){

}
Obstacle::~Obstacle(){

}

void Obstacle::update(unsigned int _time) override{

}
int Obstacle::getType() override {

}

unsigned int Obstacle::getWidth(){
    return this->width;
}
unsigned int Obstacle::getHeight(){
    return this->height;
}
int Obstacle::getAngle(){
    return this->angle;
}

void Obstacle::setWidth(unsigned int _width){
    this->width = _width;
}
void Obstacle::setHeight(unsigned int _height){
    this->height = _height;
}
void Obstacle::setAngle(int _angle){
    this->angle = _angle;
}