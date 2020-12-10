#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ServerWorld.hpp"

TEST(BasicTest, TryTest) {
    ServerWorld sw;
    sw.startGame();
    sw.addEvent(0, PLAYER_CONNECTED, 1);
    sw.addEvent(6, BUTTON_UP, 1);
    sleep(1);
    sw.addEvent(0, PLAYER_CONNECTED, 1);
    sw.addEvent(7, COMMAND_SHOOT, 1);
    sleep(1);
    sw.addEvent(6, BUTTON_UP, 0);
    auto obj = sw.getObjects(6);
    for (auto o : obj) {
        std::cout << o->getId() << ": " << o->getCoordinates().x << " " << o->getCoordinates().y << std::endl;
    }
    sw.endGame();
}