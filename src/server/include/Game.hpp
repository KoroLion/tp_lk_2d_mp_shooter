#ifndef TP_LK_2D_MP_SHOOTER_GAME_H

#include "Map.hpp"

class Game{
public:
    Game();
    ~Game();

    void UpdateObject(unsigned int _id, Command _command, int args);
    void UpdateMap(unsigned int _time);

    //returns all objects, which object with id == _id can see
    std::vector<GameObject *> GetObjects(unsigned int _id);

    //checks collision for all obejcts
    void CheckCollisions();
private:
    unsigned int time;
    Map *map;
};
#define TP_LK_2D_MP_SHOOTER_GAME_H

#endif //TP_LK_2D_MP_SHOOTER_GAME_H
