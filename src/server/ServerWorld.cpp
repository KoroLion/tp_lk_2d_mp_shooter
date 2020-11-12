#include "ServerWorld.hpp"

ServerWorld::ServerWorld(){

}
ServerWorld::~ServerWorld(){

}

void ServerWorld::startGame(){

}
void ServerWorld::endGame(){

}

//called by GameServer for each event
void ServerWorld::addEvent(unsigned int _id, Command _command, int args){

}

//called by GameServer and returns all objects, which object with id == _id can see
std::vector<GameObject *> ServerWorld::getObjects(unsigned int _id){

}
void ServerWorld::processEvents(){

}