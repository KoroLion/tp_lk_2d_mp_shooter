#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ServerWorld.hpp"

TEST(BasicTest, TryTest) {
    ServerWorld sw;
    sw.startGame();
    auto player = sw.createPlayer(30, 30);
    sw.addEvent(player, BUTTON_UP, 1);
    sleep(1);
    auto player2 = sw.createPlayer(97, 91);
    sw.addEvent(player2, COMMAND_SHOOT, 1);
    sleep(1);
    sw.addEvent(player, BUTTON_UP, 0);
    auto obj = sw.getObjects(player);
    for (auto o : obj) {
        std::cout << o->getId() << ": " << o->getCoordinates().x << " " << o->getCoordinates().y << std::endl;
    }
    sw.endGame();
}