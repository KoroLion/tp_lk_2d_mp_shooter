#include "Player.hpp"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

Player::Player(unsigned int _id,
               Coordinates _coord,
               Type _type,
               std::chrono::time_point<std::chrono::steady_clock> _time,
               MoveDirection _direction,
               float _angle,
               float _hp,
               float _width,
               float _height,
               float _speed,
               unsigned int _bullets) :
               GameObject(_id, _coord, _type, _time, _direction, _angle, _hp, _width, _height) {
    this->speed = _speed;
    this->bullets = _bullets;
}

Player::~Player() {}

bool Player::update(std::chrono::time_point<std::chrono::steady_clock> _time){
    std::chrono::duration<float> deltaTime = _time - this->getTime();
    this->setTime(_time);
    if (this->getDirection() == NO_MOVE)
        return true;
    GameObject::update(_time);
    float deltaCoord = deltaTime.count() * this->speed;
    float curAngle = this->getAngle();
    switch (this->getDirection()) {
        case BACK :
            curAngle += 180;
            break;
        case RIGHT :
            curAngle += 90;
            break;
        case LEFT :
            curAngle -= 90;
            break;
        default:
            break;
    }
    Coordinates coord = this->getCoordinates();
    coord.x += deltaCoord * std::cos(curAngle/180 * M_PI);
    coord.y += deltaCoord * std::sin(curAngle/180 * M_PI);
    this->setCoordinates(coord);
    return true;
}

Type Player::getType() const {
    return PLAYER;
}

void Player::reload(unsigned int _bullets) {
    this->bullets = _bullets;
}

bool Player::shoot() {
    if (bullets == 0)
        return false;
    --bullets;
    return true;
}