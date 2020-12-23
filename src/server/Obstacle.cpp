#include "Obstacle.hpp"


Obstacle::Obstacle(unsigned int _id,
                   Coordinates _coord,
                   Type _type,
                   std::chrono::time_point<std::chrono::steady_clock> _time,
                   MoveDirection _direction,
                   float _angle,
                   float _hp,
                   float _width,
                   float _height
                   ) : GameObject(_id, _coord, _type, _time, _direction, _angle, _hp, _width, _height) {}

Obstacle::~Obstacle() {}

Type Obstacle::getType() const{
    return OBSTACLE;
}

float Obstacle::getHp(){
    this->setHp(1);
    return 1;
}
