#ifndef TP_LK_2D_MP_SHOOTER_BULLET_H
#define TP_LK_2D_MP_SHOOTER_BULLET_H

#include "GameObject.hpp"
class Techinc : public GameObject{
public:
    Bullet();
    ~Bullet();

    void update(unsigned int _time) override;
    int getType() override ;

    int getAngle();
    unsigned int getSpeed();
    unsigned int getDamage();

    void setAngle(int);
    void setSpeed(unsigned int);
    void setDamage(unsigned int);
private:
    int angle;
    unsigned int speed;
    unsigned int damage;
};
#endif //TP_LK_2D_MP_SHOOTER_BULLET_H
