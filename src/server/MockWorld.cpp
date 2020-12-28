/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include <vector>

#include "include/MockWorld.hpp"
#include "include/utils.hpp"

World::World() {
    _game_objects.push_back(GameObject(1, 10, 10, 1, 0));
    _game_objects.push_back(GameObject(2, 15, 15, 0, 1));
    _game_objects.push_back(GameObject(3, 20, 20, 1, 1));
}

void World::update() {
    for (auto itr = _game_objects.begin(); itr != _game_objects.end(); itr++) {
        itr->update();
    }
}

void World::start() {
    _is_running = true;
    while (_is_running) {
        update();
        sleep_ms(1000);
    }
}

void World::stop() {
    _is_running = false;
}

const std::vector<GameObject>& World::get_game_objects(int id) {
    return _game_objects;
}
