#ifndef TP_LK_2D_MP_SHOOTER_OBSTACLE_H
#define TP_LK_2D_MP_SHOOTER_OBSTACLE_H

#include "GameObject.hpp"
class Obstacle : public GameObject{
public:
    Obstacle(unsigned int _id,
             Coordinates coord,
             Type _type,
             std::chrono::time_point<std::chrono::steady_clock> _time,
             MoveDirection _direction,
             float _angle,
             float _hp,
             float _width,
             float _height);
    ~Obstacle();

    Type getType() const override ;

    float getHp() override;
};
#endif //TP_LK_2D_MP_SHOOTER_OBSTACLE_H
