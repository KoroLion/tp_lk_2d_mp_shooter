#ifndef TP_LK_2D_MP_SHOOTER_TECHNICS_H
#define TP_LK_2D_MP_SHOOTER_TECHNICS_H

#include "GameObject.hpp"
class Technics : public GameObject{
public:
    Technics(unsigned int _id,
            Coordinates _coord,
            Type _type,
            std::chrono::time_point<std::chrono::steady_clock> _time,
            float _angle,
            float _hp,
            float _width,
            float _height,
            float _speed,
            unsigned int _capacity);
    ~Technics();

    bool update(std::chrono::time_point<std::chrono::steady_clock> _time) override;
    Type getType() const override ;
private:
    float speed;
    unsigned int capacity;
};
#endif //TP_LK_2D_MP_SHOOTER_TECHNICS_H
