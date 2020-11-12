#include "Game.hpp"

Game::Game(){

}

Game::~Game(){

}


void Game::updateObject(unsigned int _id, Command _command, int args){

}

void Game::updateMap(unsigned int _time){

}


//returns all objects, which object with id == _id can see
std::vector<GameObject *> Game::getObjects(unsigned int _id){

}


//checks collision for all obejcts
void Game::checkCollisions(){

}
