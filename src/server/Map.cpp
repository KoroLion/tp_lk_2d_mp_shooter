#include "Map.hpp"

Map::Map(){}

Map::Map(float _height, float _width) {
    this->height = _height;
    this->width = _width;
    this->ids = 0;
}

Map::~Map(){}

void Map::updateObjects(std::chrono::time_point<std::chrono::steady_clock> _time) {
    for (auto object : this->objects ) {
        if (!object.second->update(_time)) {
            this->objects.erase(object.first);
        }
    }
    checkCollisions();
}

void Map::setObjectDirection(unsigned int _id, MoveDirection direction, std::chrono::time_point<std::chrono::steady_clock> _time) {
    std::shared_ptr<GameObject> obj(this->objects.at(_id));
    obj->setDirection(direction);
    obj->setTime(_time);
}

void Map::turnObject(unsigned int _id, float angle, std::chrono::time_point<std::chrono::steady_clock> _time) {
    std::shared_ptr<GameObject> obj(this->objects.at(_id));
    obj->setAngle(angle);
    obj->setTime(_time);
}

void Map::reload(unsigned int _id, unsigned int _bullets, std::chrono::time_point<std::chrono::steady_clock> _time){
    std::shared_ptr<GameObject> obj = this->objects.at(_id);
    obj->reload(_bullets);
}

void Map::shoot(unsigned int _id, std::shared_ptr<GameObject> bullet) {
    std::shared_ptr<GameObject> obj = this->objects.at(_id);
    if (!obj->shoot())
        return;
    bullet->setId(this->ids);
    bullet->setCoordinates(obj->getCoordinates());
    bullet->setAngle(obj->getAngle());
    this->objects[this->ids] = bullet;
    ++this->ids;
}

 unsigned int Map::addObject(std::shared_ptr<GameObject> object) {
    object->setId(this->ids);
    this->objects[this->ids] = object;
    ++this->ids;
    return this->ids - 1;
}


void Map::removeObject(unsigned int _id) {
    this->objects.erase(_id);
}

std::shared_ptr<GameObject> Map::getObject(unsigned int _id) {
    return this->objects.at(_id);
}

//returns all objects, which object with id == _id can see
std::vector<std::shared_ptr<GameObject>> Map::getObjects(unsigned int _id) {
    std::vector<std::shared_ptr<GameObject>> vec;
    for (auto val : this->objects) {
        vec.push_back(val.second);
    }
    return vec;
}

//checks collision for all objects
void Map::checkCollisions(){
    Coordinates a_max, b_max, a_min, b_min;
    for (auto a = this->objects.begin(); a != this->objects.end(); ++a) {
        if (a->second->minCoord().x < 0 || a->second->minCoord().y < 0)
            a->second->reverseUpdate();
        if (a->second->maxCoord().x > this->width || a->second->maxCoord().y > this->height)
            a->second->reverseUpdate();
        for (auto b = a; b != this->objects.end(); ++b) {
            if(a == b)
                continue;

            a_max = a->second->maxCoord();
            b_max = b->second->maxCoord();
            a_min = a->second->minCoord();
            b_min = b->second->minCoord();

            if (a_min.x < b_max.x && a_max.x > b_min.x && a_min.y < b_max.y && a_max.y > b_min.y) {
                resolveCollision(a->second, b->second);
            }
        }
    }
}

//resolve collision for two objects with ids: _id1 and _id2
void Map::resolveCollision(std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b){
    a->reverseUpdate();
    b->reverseUpdate();
    a->reduceHp(b->getDamage());
    b->reduceHp(a->getDamage());
    if (a->getHp() <= 0) {
        this->objects.erase(a->getId());
    }
    if (b->getHp() <= 0) {
        this->objects.erase(b->getId());
    }
}