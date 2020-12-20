#ifndef SRC_TESTS_MOCKWORLD_HPP_
#define SRC_TESTS_MOCKWORLD_HPP_

#include <gtest/gmock.h>

class GameObject {
};

class Event {
};

class MockWorld {
 public:
    MOCK_METHOD1(get_objects, std::vector<GameObject*>(int id));
    MOCK_METHOD2(add_event, void(int id, Event e));
};

#endif  // SRC_TESTS_MOCKWORLD_HPP_
