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


    virtual Type getType() const = 0;

    Coordinates minCoord() const;
    Coordinates maxCoord() const;

    unsigned int getId() const;
    void setId(unsigned int _id);

    Coordinates getCoordinates() const;
    void setCoordinates(Coordinates _coordinates);
    float getX() const;
    float getY() const;

    std::chrono::time_point<std::chrono::steady_clock> getTime() const ;
    void setTime(std::chrono::time_point<std::chrono::steady_clock> _time);

    virtual float getHp();
    void setHp(float _hp);
    void reduceHp(float _damage);

    MoveDirection getDirection() const;
    void setDirection(MoveDirection _direction);

    float getAngle() const;
    void setAngle(float _angle);

    float getWidth() const;
    float getHeight() const;

    void setWidth(float _width);
    void setHeight(float _height);

    virtual float getDamage() const;
    virtual void reload(unsigned int _bullets);
    virtual bool shoot();
    virtual unsigned int getOwner() const;
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
