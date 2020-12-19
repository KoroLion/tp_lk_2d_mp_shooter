#include "ServerWorld.hpp"
#include <iostream>

ServerWorld::ServerWorld() {
    game = std::make_shared<Game>();
    std::cout << "Game created" << std::endl;
}

ServerWorld::~ServerWorld() {
    std::cout << "Game destroyed" << std::endl;
}

void ServerWorld::startGame(){
    game->start();
    std::cout << "Game started" << std::endl;


    this->eventsThread = std::thread(&ServerWorld::handleEvents, this);
}

void ServerWorld::endGame() {
    game->end();
    this->eventsThread.join();
    std::cout << "Game ended" << std::endl;
    while (!events.empty()) {
        events.pop();
    }
}

bool ServerWorld::isRunning() const{
    return game->isRunning();
}

//called by GameServer for each event
void ServerWorld::addEvent(unsigned int _id, Command _command, int _args) {
    const std::lock_guard<std::mutex> lock(mutex);
    events.emplace(Event(_id, _command, _args));
}

//called by GameServer and returns all objects, which object with id == _id can see
std::vector<std::shared_ptr<GameObject>> ServerWorld::getObjects(unsigned int _id) {
    auto obj = game->getObjects(_id);
    return obj;
}


void ServerWorld::handleEvents() {
    while (game->isRunning()) {
        Event event;
        mutex.lock();
        if (!events.empty()) {
            event = events.front();
            events.pop();
        }
        mutex.unlock();
        if (!event.isEmpty)
            game->updateObject(event.id, event.command, event.args);
    }
}