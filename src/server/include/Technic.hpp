#ifndef TP_LK_2D_MP_SHOOTER_TECHNIC_H
#define TP_LK_2D_MP_SHOOTER_TECHNIC_H

#include "GameObject.hpp"
class Technic : public GameObject{
public:
    Technic();
    ~Technic();

    void Update(unsigned int _time) override;
    int GetType() override ;

    unsigned int GetWidth();
    unsigned int GetHeight();
    int GetAngle();
    unsigned int GetSpeed();
    unsigned int GetHp();
    unsigned int GetDamage();

    void SetWidth(unsigned int);
    void SetHeight(unsigned int);
    void SetAngle(int);
    void SetSpeed(unsigned int);
    void SetHp(unsigned int);
    void SetDamage(unsigned int);
private:
    unsigned int width;
    unsigned int height;
    int angle;
    unsigned int speed;
    unsigned int damage;
    unsigned int hp;
};
#endif //TP_LK_2D_MP_SHOOTER_TECHNIC_H
