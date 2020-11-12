#ifndef TP_LK_2D_MP_SHOOTER_BULLET_H
#define TP_LK_2D_MP_SHOOTER_BULLET_H

#include "GameObject.h"
class Techinc : public GameObject{
public:
    Bullet();
    ~Bullet();

    void Update(unsigned int _time) override;
    int GetType() override ;

    int GetAngle();
    unsigned int GetSpeed();
    unsigned int GetDamage();

    void SetAngle(int);
    void SetSpeed(unsigned int);
    void SetDamage(unsigned int);
private:
    int angle;
    unsigned int speed;
    unsigned int damage;
};
#endif //TP_LK_2D_MP_SHOOTER_BULLET_H
