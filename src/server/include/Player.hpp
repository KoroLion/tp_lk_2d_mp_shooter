#ifndef TP_LK_2D_MP_SHOOTER_PLAYER_H
#define TP_LK_2D_MP_SHOOTER_PLAYER_H

#include "GameObject.hpp"

class Player : public GameObject {
public:
    Player();
    ~Player();

    void update(unsigned int _time) override;
    int getType() override ;

    int getRadius();
    int getAngle();
    unsigned int getSpeed();
    unsigned int getHp();
    unsigned int getDamage();

    void setRadius(int);
    void setAngle(int);
    void setSpeed(unsigned int);
    void setHp(unsigned int);
    void setDamage(unsigned int);
private:
    int radius;
    int angle;
    unsigned int speed;
    unsigned int hp;
    unsigned int damage;
};
#endif //TP_LK_2D_MP_SHOOTER_PLAYER_H
