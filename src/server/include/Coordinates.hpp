#ifndef TP_LK_2D_MP_SHOOTER_COORDINATES_H

struct Coordinates{
    Coordinates() : x(0), y(0) {}
    Coordinates(float _x, float _y) : x(_x), y(_y) {}
    bool operator <(const Coordinates& rhs) {
        return this->x < rhs.x || this->y < rhs.y;
    }

    bool operator >(const Coordinates& rhs) {
        return this->x > rhs.x || this->y > rhs.y;
    }

    float x;
    float y;
};
#define TP_LK_2D_MP_SHOOTER_COORDINATES_H

#endif //TP_LK_2D_MP_SHOOTER_COORDINATES_H
