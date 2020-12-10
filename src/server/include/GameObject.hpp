#ifndef TP_LK_2D_MP_SHOOTER_GAMEOBJECT_H

#include "Coordinates.hpp"
#include <memory>
#include <cmath>
#include <thread>
#include <chrono>
#include <iostream>

enum MoveDirection{
    NO_MOVE,
    FORWARD,
    BACK,
    LEFT,
    RIGHT
};

enum Type {
    PLAYER,
    TECHNICS,
    OBSTACLE,
    BULLET
};

class GameObject{
public:
    GameObject(unsigned int _id,
            Coordinates _coord,
            Type _type,
            std::chrono::time_point<std::chrono::steady_clock> _time,
            MoveDirection _direction,
            float _angle,
            float _hp,
            float _width,
            float _height);

    virtual ~GameObject() = 0;

    virtual bool update(std::chrono::time_point<std::chrono::steady_clock> _time);

    virtual void reverseUpdate();


    virtual Type getType() = 0;

    Coordinates minCoord();
    Coordinates maxCoord();

    unsigned int getId();
    void setId(unsigned int _id);

    Coordinates getCoordinates();
    void setCoordinates(Coordinates _coordinates);

    std::chrono::time_point<std::chrono::steady_clock> getTime();
    void setTime(std::chrono::time_point<std::chrono::steady_clock> _time);

    virtual float getHp();
    void setHp(float _hp);
    void reduceHp(float _damage);

    MoveDirection getDirection();
    void setDirection(MoveDirection _direction);

    float getAngle();
    void setAngle(float _angle);

    float getWidth();
    float getHeight();

    void setWidth(float _width);
    void setHeight(float _height);

    virtual float getDamage();
private:
    unsigned int id;
    Coordinates coordinates;
    Coordinates previousCoordinates;
    Type type;
    std::chrono::time_point<std::chrono::steady_clock> timeModified;
    MoveDirection direction;
    float angle;
    float hp;
    float width;
    float height;
};
#define TP_LK_2D_MP_SHOOTER_GAMEOBJECT_H

#endif //TP_LK_2D_MP_SHOOTER_GAMEOBJECT_H
