#ifndef TP_LK_2D_MP_SHOOTER_MAP_H
#define TP_LK_2D_MP_SHOOTER_MAP_H

#include <map>
#include <vector>
#include "GameObject.hpp"
#include "Command.hpp"

class Map{
public:
    Map(unsigned int _height, unsigned int _width, std::map<unsigned int, GameObject *>);
    ~Map();

    void addObjects(std::map<unsigned int, GameObject *>);
    void updateObjects(unsigned int _time);
    void updateObject(unsigned int _id, Command _command, unsigned int _arg);
    void deleteObject(unsigned int _id);

    GameObject *getObject(unsigned int _id);

    //returns all objects, which object with id == _id can see
    std::vector<GameObject *> getObjects(unsigned int _id);

    //checks collision for all obejcts
    void checkCollisions(unsigned int _time);

private:
    //checks collision for object with id == _id with other objects
    void collision(unsigned int _id);
    //resolve collision for two objects with ids: _id1 and _id2
    void resolveCollision(unsigned int _id1, unsigned int _id2);

    unsigned int height;
    unsigned int width;
    std::map<unsigned int, GameObject *>;
};

#endif //TP_LK_2D_MP_SHOOTER_MAP_H
