#ifndef TP_LK_2D_MP_SHOOTER_MAP_H
#define TP_LK_2D_MP_SHOOTER_MAP_H

#include <map>
#include <vector>
#include "GameObject.h"
#include "Command.h"

class Map{
public:
    Map(unsigned int _height, unsigned int _width, std::map<unsigned int, GameObject *>);
    ~Map();

    void AddObjects(std::map<unsigned int, GameObject *>);
    void UpdateObjects(unsigned int _time);
    void UpdateObject(unsigned int _id, Command _command, unsigned int _arg);

    GameObject *GetObject(unsigned int _id);

    //returns all objects, which object with id == _id can see
    std::vector<GameObject *> GetObjects(unsigned int _id);

    //checks collision for all obejcts
    void CheckCollisions();

private:
    //checks collision for object with id == _id with other objects
    void Collision(unsigned int _id);
    //resolve collision for two objects with ids: _id1 and _id2
    void ResolveCollision(unsigned int _id1, unsigned int _id2);

    unsigned int height;
    unsigned int width;
    std::map<unsigned int, GameObject *>;
};

#endif //TP_LK_2D_MP_SHOOTER_MAP_H
