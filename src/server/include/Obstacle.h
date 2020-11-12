#ifndef TP_LK_2D_MP_SHOOTER_OBSTACLE_H
#define TP_LK_2D_MP_SHOOTER_OBSTACLE_H

#include "GameObject.h"
class Obstacle : public GameObject{
public:
    Obstacle();
    ~Obstacle();

    void Update(unsigned int _time) override;
    int GetType() override ;

    unsigned int GetWidth();
    unsigned int GetHeight();
    int GetAngle();

    void SetWidth(unsigned int);
    void SetHeight(unsigned int);
    void SetAngle(int);
private:
    unsigned int width;
    unsigned int height;
    int angle;
};
#endif //TP_LK_2D_MP_SHOOTER_OBSTACLE_H
