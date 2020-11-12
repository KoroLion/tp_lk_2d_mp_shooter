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

    virtual void Update(unsigned int _time) = 0;
    virtual int GetType() = 0;

    unsigned int GetId();
    void SetId();

    Coordinates GetCoordinates();
    void SetCoordinates();

    unsigned int GetTime();
    void SetTime();

    MoveDirection GetDirection();
    void SetDirection(MoveDirection _direction);

private:
    unsigned int id;
    Coordinates coordinates;
    int type;
    unsigned int timeModified;
    MoveDirection direction;
};
#define TP_LK_2D_MP_SHOOTER_GAMEOBJECT_H

#endif //TP_LK_2D_MP_SHOOTER_GAMEOBJECT_H
