#include "Game.h"

Game::Game(){

}

Game::~Game(){

}


void Game::UpdateObject(unsigned int _id, Command _command, int args){

}

void Game::UpdateMap(unsigned int _time){

}


//returns all objects, which object with id == _id can see
std::vector<GameObject *> Game::GetObjects(unsigned int _id){

}


//checks collision for all obejcts
void Game::CheckCollisions(){

}
