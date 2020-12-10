#ifndef TP_LK_2D_MP_SHOOTER_BULLET_H
#define TP_LK_2D_MP_SHOOTER_BULLET_H

#include "GameObject.hpp"
class Bullet : public GameObject{
public:
    Bullet(unsigned int _id,
           Coordinates _coord,
           Type _type,
           std::chrono::time_point<std::chrono::steady_clock> _time,
           MoveDirection _direction,
           float _angle,
           float _hp,
           float _width,
           float _height,
           float _speed,
           float _damage,
           float _acceleration,
           float _minSpeed);
    ~Bullet();

    bool update(std::chrono::time_point<std::chrono::steady_clock> _time) override;
    void reverseUpdate() override;
    Type getType() override ;

    float getDamage() override ;

private:
    float speed;
    float damage;
    float acceleration;
    float minSpeed;
};
#endif //TP_LK_2D_MP_SHOOTER_BULLET_H
