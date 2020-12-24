#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ServerWorld.hpp"
using namespace std::literals::chrono_literals;

TEST(BasicTest, ConnectDisconnectPlayer) {
    ServerWorld sw;
    sw.startGame();
    auto objects = sw.getObjects(0);
    int num_objects = objects.size();
    auto player = sw.connectPlayer();
    objects = sw.getObjects(player);
    int num_objects_with_player = objects.size();
    EXPECT_EQ(num_objects + 1, num_objects_with_player);
    sw.disconnectPlayer(player);
    objects = sw.getObjects(0);
    int num_objects_without_player = objects.size();
    EXPECT_EQ(num_objects, num_objects_without_player);
    sw.endGame();
}

