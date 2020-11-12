#ifndef SRC_TESTS_MOCKWORLD_HPP_
#define SRC_TESTS_MOCKWORLD_HPP_

class GameObject {
};

class MockWorld {
 public:
    MOCK_METHOD1(get_objects, std::vector<GameObject*>(int id));
    MOCK_METHOD0(add_event, void());
};

#endif  // SRC_TESTS_MOCKWORLD_HPP_
