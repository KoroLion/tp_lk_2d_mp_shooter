/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#ifndef SRC_CLIENT_INCLUDE_EQUIPMENTS_HPP_
#define SRC_CLIENT_INCLUDE_EQUIPMENTS_HPP_

#include "SDL.h"

// 1st floor---------
class Equipment {
 public:
    Equipment(int x, int y, float _rotation): x(x), y(y), rotation(_rotation) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

    virtual ~Equipment();

 protected:
    float x, y, rotation;
};

// 2nd floor---------
class Armor: public Equipment {
 public:
    Armor(int x, int y, float rotation, float _percent, float _hp):
        Equipment(x, y, rotation), percent(_percent), hp(_hp) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

    virtual ~Armor();

 protected:
    float hp;
    const float percent;
};

class Weapon: public Equipment {
 public:
    Weapon(int x, int y, float rotation, float _damage, float _timeReload, float _timeFireRate, int _capacity):
        Equipment(x, y, rotation), damage(_damage), timeReload(_timeReload), timeFireRate(_timeFireRate), capacity(_capacity) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

    virtual ~Weapon();

 protected:
    int width, height;
    float damage, timeReload, timeFireRate;
    const int capacity;
};

class Grenade: public Equipment {
 public:
    Grenade(int x, int y, float _rotation, float _damage, float _range, float _startSpeed, float _timeDetonate):
        Equipment(x, y, _rotation), damage(_damage), range(_range), startSpeed(_startSpeed), timeDetonate(_timeDetonate) {;}

    virtual void render(SDL_Renderer *renderer);
    virtual void update();

    virtual ~Grenade();

 protected:
    int width, height;
    float damage, range, startSpeed, timeDetonate;
};

//3rd floor--------
//some concrete veapons, heavy/lite armors, smoke/light bombs e.t.c

#endif  // SRC_CLIENT_INCLUDE_EQUIPMENTS_HPP_
