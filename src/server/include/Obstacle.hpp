#ifndef TP_LK_2D_MP_SHOOTER_OBSTACLE_H
#define TP_LK_2D_MP_SHOOTER_OBSTACLE_H

#include "GameObject.hpp"
class Obstacle : public GameObject{
public:
    Obstacle();
    ~Obstacle();

    void update(unsigned int _time) override;
    int getType() override ;

    unsigned int getWidth();
    unsigned int getHeight();
    int getAngle();

    void setWidth(unsigned int);
    void setHeight(unsigned int);
    void setAngle(int);
private:
    unsigned int width;
    unsigned int height;
    int angle;
};
#endif //TP_LK_2D_MP_SHOOTER_OBSTACLE_H
