#ifndef TP_LK_2D_MP_SHOOTER_PLAYER_H
#define TP_LK_2D_MP_SHOOTER_PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    Player();
    ~Player();

    void Update(unsigned int _time) override;
    int GetType() override ;

    int GetRadius();
    int GetAngle();
    unsigned int GetSpeed();
    unsigned int GetHp();
    unsigned int GetDamage();

    void SetRadius(int);
    void SetAngle(int);
    void SetSpeed(unsigned int);
    void SetHp(unsigned int);
    void SetDamage(unsigned int);
private:
    int radius;
    int angle;
    unsigned int speed;
    unsigned int hp;
    unsigned int damage;
};
#endif //TP_LK_2D_MP_SHOOTER_PLAYER_H
