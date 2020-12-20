#ifndef SRC_SERVER_INCLUDE_WORLD_HPP_
#define SRC_SERVER_INCLUDE_WORLD_HPP_

#include <vector>
#include "utils.hpp"

class Event {
};

class GameObject {
 private:
    int type_id;
    float x, y;
    float speedX, speedY;

 public:
    GameObject(int type_id, float x, float y, float speedX, float speedY)
        : type_id(type_id), x(x), y(y), speedX(speedX), speedY(speedY) {}

    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_type_id() const { return type_id; }

    void update() {
        x += speedX;
        y += speedY;
    }
};

class World {
 private:
     std::vector<GameObject> _game_objects;
     bool _is_running = false;
 public:
    World() {
        _game_objects.push_back(GameObject(1, 10, 10, 1, 0));
        _game_objects.push_back(GameObject(2, 15, 15, 0, 1));
        _game_objects.push_back(GameObject(3, 20, 20, 1, 1));
    }
    ~World() {}

    void update() {
        for (auto itr = _game_objects.begin(); itr != _game_objects.end(); itr++) {
            itr->update();
        }
    }

    void start() {
        _is_running = true;
        while (_is_running) {
            update();
            sleep_ms(1000);
        }
    }

    void stop() {
        _is_running = false;
    }

    const std::vector<GameObject>& get_game_objects(int id) {
        return _game_objects;
    }

    void add_event(int id, Event e) {}
};

#endif  // SRC_SERVER_INCLUDE_WORLD_HPP_
