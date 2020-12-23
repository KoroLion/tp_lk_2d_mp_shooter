#include <Command.hpp>
#include "Player.hpp"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

Player::Player(unsigned int _id,
               Coordinates _coord,
               Type _type,
               std::chrono::time_point<std::chrono::steady_clock> _time,
               float _angle,
               float _hp,
               float _width,
               float _height,
               float _speed,
               unsigned int _bullets) :
               GameObject(_id, _coord, _type, _time, _angle, _hp, _width, _height) {
    this->speed = _speed;
    this->bullets = _bullets;
    for (auto &i : buttons) {
        i = false;
    }
    moving = false;
}

Player::~Player() {}


bool Player::update(std::chrono::time_point<std::chrono::steady_clock> _time){
    std::chrono::duration<float> deltaTime = _time - this->getTime();
    this->setTime(_time);
    if (!this->isMoving())
        return true;
    GameObject::update(_time);
    float deltaCoord = deltaTime.count() * this->speed;
    float curAngle = this->getAngle();
    Coordinates coord = this->getCoordinates();

    if ((int)buttons[0] + (int)buttons[1] + (int)buttons[2] + (int)buttons[3] > 1)
        deltaCoord /= sqrt(2);

    if (this->buttons[BUTTON_UP])
        coord = computeCoordinates(coord, deltaCoord, curAngle);
    if (this->buttons[BUTTON_LEFT])
        coord = computeCoordinates(coord, deltaCoord, curAngle - 90);
    if (this->buttons[BUTTON_RIGHT])
        coord = computeCoordinates(coord, deltaCoord, curAngle + 90);
    if (this->buttons[BUTTON_DOWN])
        coord = computeCoordinates(coord, deltaCoord, curAngle + 180);


    this->setCoordinates(coord);
    return true;
}


Coordinates Player::computeCoordinates(Coordinates coord, float deltaCoord, float curAngle) {
    coord.x += deltaCoord * std::cos(curAngle/180 * M_PI);
    coord.y += deltaCoord * std::sin(curAngle/180 * M_PI);
    return coord;
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

bool Player::isMoving() const{
    return moving;
}

void Player::setButton(Command _button, bool pressed) {
    this->buttons[_button] = pressed;
    for (auto i : this->buttons) {
        if (i) {
            moving = true;
            return;
        }
    }
    moving = false;
}
