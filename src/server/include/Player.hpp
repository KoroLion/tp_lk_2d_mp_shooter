#ifndef TP_LK_2D_MP_SHOOTER_PLAYER_H
#define TP_LK_2D_MP_SHOOTER_PLAYER_H

#include "GameObject.hpp"


class Player : public GameObject {
public:
    Player(unsigned int _id,
            Coordinates _coord,
            Type _type,
            std::chrono::time_point<std::chrono::steady_clock> _time,
            float _angle,
            float _hp,
            float _width,
            float _height,
            float _speed,
            unsigned int _bullets);
    ~Player();

    bool update(std::chrono::time_point<std::chrono::steady_clock> _time) override;
    Type getType() const override ;
    void reload(unsigned int _bullets) override ;
    bool shoot() override ;
    bool isMoving() const override ;
    void setButton(Command _button, bool pressed) override ;
private:
    Coordinates computeCoordinates(Coordinates coord, float deltaCoord, float curAngle);

    float speed;
    float bullets;

    bool moving;
    bool buttons[4];
};
#endif //TP_LK_2D_MP_SHOOTER_PLAYER_H
