#ifndef TP_LK_2D_MP_SHOOTER_GAMEOBJECT_H

#include "Coordinates.hpp"

enum MoveDirection{
    NO_MOVE,
    FORWARD,
    BACK,
    LEFT,
    RIGHT
};

class GameObject{
public:
    GameObject();
    virtual ~GameObject() = 0;

    virtual void update(unsigned int _time) = 0;
    virtual int getType() = 0;

    unsigned int getId();
    void setId(unsigned int);

    Coordinates getCoordinates();
    void setCoordinates(Coordinates);

    unsigned int getTime();
    void setTime(unsigned int);

    MoveDirection getDirection();
    void setDirection(MoveDirection _direction);

private:
    unsigned int id;
    Coordinates coordinates;
    int type;
    unsigned int timeModified;
    MoveDirection direction;
};
#define TP_LK_2D_MP_SHOOTER_GAMEOBJECT_H

#endif //TP_LK_2D_MP_SHOOTER_GAMEOBJECT_H
