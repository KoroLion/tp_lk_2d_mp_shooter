#ifndef TP_LK_2D_MP_SHOOTER_TECHNIC_H
#define TP_LK_2D_MP_SHOOTER_TECHNIC_H

#include "GameObject.hpp"
class Technic : public GameObject{
public:
    Technic();
    ~Technic();

    void update(unsigned int _time) override;
    int getType() override ;

    unsigned int getWidth();
    unsigned int getHeight();
    int getAngle();
    unsigned int getSpeed();
    unsigned int getHp();
    unsigned int getDamage();

    void setWidth(unsigned int);
    void setHeight(unsigned int);
    void setAngle(int);
    void setSpeed(unsigned int);
    void setHp(unsigned int);
    void setDamage(unsigned int);
private:
    unsigned int width;
    unsigned int height;
    int angle;
    unsigned int speed;
    unsigned int damage;
    unsigned int hp;
};
#endif //TP_LK_2D_MP_SHOOTER_TECHNIC_H
