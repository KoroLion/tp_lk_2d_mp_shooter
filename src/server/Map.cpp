#include "Map.hpp"

Map::Map(unsigned int _height, unsigned int _width, std::map<unsigned int, GameObject *>){

}

Map::~Map(){

}

void Map::addObjects(std::map<unsigned int, GameObject *>){

}
void Map::updateObjects(unsigned int _time){

}
void Map::updateObject(unsigned int _id, Command _command, unsigned int _arg){

}

GameObject *Map::getObject(unsigned int _id){

}

//returns all objects, which object with id == _id can see
std::vector<GameObject *> Map::getObjects(unsigned int _id){

}

//checks collision for all obejcts
void Map::checkCollisions(){

}

//checks collision for object with id == _id with other objects
void Map::collision(unsigned int _id){

}
//resolve collision for two objects with ids: _id1 and _id2
void Map::resolveCollision(unsigned int _id1, unsigned int _id2){

}