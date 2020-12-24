#include "ServerWorld.hpp"
#include <iostream>

ServerWorld::ServerWorld() {
    game = std::make_shared<Game>();
}

ServerWorld::~ServerWorld() {
}

void ServerWorld::startGame(){
    game->start();

    this->eventsThread = std::thread(&ServerWorld::handleEvents, this);
}

void ServerWorld::endGame() {
    game->end();
    this->eventsThread.join();
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

unsigned int ServerWorld::connectPlayer() {
    return game->createPlayer();
}

void ServerWorld::disconnectPlayer(unsigned int _id) {
    game->removePlayer(_id);
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