#ifndef TP_LK_2D_MP_SHOOTER_MAP_H
#define TP_LK_2D_MP_SHOOTER_MAP_H

#include <map>
#include <vector>
#include "GameObject.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Obstacle.hpp"
#include "Technics.hpp"
#include "Command.hpp"

class Map{
public:
    Map();
    Map(float _height, float _width);
    ~Map();

    void updateObjects(std::chrono::time_point<std::chrono::steady_clock> _time);

    void setButton(unsigned int _id, Command _button, bool pressed, std::chrono::time_point<std::chrono::steady_clock> _time);
    void turnObject(unsigned int _id, float angle, std::chrono::time_point<std::chrono::steady_clock> _time);
    void reload(unsigned int _id, unsigned int _bullets, std::chrono::time_point<std::chrono::steady_clock> _time);

    void shoot(unsigned int _id, std::shared_ptr<GameObject> _bullet);

    unsigned int addObject(std::shared_ptr<GameObject> _object);

    void removeObject(unsigned int _id);

    std::shared_ptr<GameObject> getObject(unsigned int _id) const;

    //returns all objects, which object with id == _id can see
    std::vector<std::shared_ptr<GameObject>> getObjects(unsigned int _id);

    bool isValid(unsigned int _id) const ;

private:
    //checks collision for all obejcts
    void checkCollisions();

    //resolve collision for two objects with ids: _id1 and _id2
    void resolveCollision(std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b);

    float height;
    float width;
    std::map<unsigned int, std::shared_ptr<GameObject>> objects;
    unsigned int ids;
};

#endif //TP_LK_2D_MP_SHOOTER_MAP_H
