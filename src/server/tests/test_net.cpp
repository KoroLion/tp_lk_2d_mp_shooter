#include <thread>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;

#include "../include/GameServer.hpp"
#include "../include/utils.hpp"

class MockWorld: public World {
 public:
    MOCK_METHOD1(get_objects, std::vector<GameObject*>(int id));
    MOCK_METHOD2(add_event, void(int id, Event e));
};

void gs_serve(GameServer *gs) {
    gs->start();
}

TEST(BasicTest, ToDoTest) {
    // MockWorld world;
    MockWorld *w = new MockWorld;
    GameServer *gs = new GameServer("0.0.0.0", 23000, w);
    std::thread gs_thread = std::thread(gs_serve, gs);
    sleep_ms(300);
    gs->stop();
    gs_thread.join();

    EXPECT_CALL((*w), get_objects)
      .Times(AtLeast(1));

    // EXPECT_EQUAL(gs->);

    delete gs;
    delete w;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
