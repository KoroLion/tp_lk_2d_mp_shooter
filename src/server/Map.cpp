#include "Map.h"

Map::Map(unsigned int _height, unsigned int _width, std::map<unsigned int, GameObject *>){

}

Map::~Map(){

}

void Map::AddObjects(std::map<unsigned int, GameObject *>){

}
void Map::UpdateObjects(unsigned int _time){

}
void Map::UpdateObject(unsigned int _id, Command _command, unsigned int _arg){

}

GameObject *Map::GetObject(unsigned int _id){

}

//returns all objects, which object with id == _id can see
std::vector<GameObject *> Map::GetObjects(unsigned int _id){

}

//checks collision for all obejcts
void Map::CheckCollisions(){

}

//checks collision for object with id == _id with other objects
void Map::Collision(unsigned int _id){

}
//resolve collision for two objects with ids: _id1 and _id2
void Map::ResolveCollision(unsigned int _id1, unsigned int _id2){

}