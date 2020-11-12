#ifndef SRC_SERVER_INCLUDE_WORLD_HPP_
#define SRC_SERVER_INCLUDE_WORLD_HPP_

#include <vector>

class Event {
};

class GameObject {
};

class World {
 public:
    ~World() {}

    std::vector<GameObject*> get_objects(int id) {
        return std::vector<GameObject*>(0);
    }
    void add_event(int id, Event e) {}
};

#endif  // SRC_SERVER_INCLUDE_WORLD_HPP_
