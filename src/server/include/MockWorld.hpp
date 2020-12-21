/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#ifndef SRC_SERVER_INCLUDE_MOCKWORLD_HPP_
#define SRC_SERVER_INCLUDE_MOCKWORLD_HPP_

#include <vector>

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
    World();
    ~World() {}

    void update();
    void start();
    void stop();

    const std::vector<GameObject>& get_game_objects(int id);
};

#endif  // SRC_SERVER_INCLUDE_MOCKWORLD_HPP_
