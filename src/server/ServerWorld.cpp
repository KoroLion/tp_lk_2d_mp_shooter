#include "ServerWorld.hpp"

ServerWorld::ServerWorld(){

}
ServerWorld::~ServerWorld(){

}

void ServerWorld::StartGame(){

}
void ServerWorld::EndGame(){

}

//called by GameServer for each event
void ServerWorld::AddEvent(unsigned int _id, Command _command, int args){

}

//called by GameServer and returns all objects, which object with id == _id can see
std::vector<GameObject *> ServerWorld::GetObjects(unsigned int _id){

}
void void PServerWorld::rocessEvents();ProcessEvents(){

}