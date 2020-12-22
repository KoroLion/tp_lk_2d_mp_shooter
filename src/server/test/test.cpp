#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ServerWorld.hpp"
using namespace std::literals::chrono_literals;

TEST(BasicTest, TryTest) {
    ServerWorld sw;
    sw.startGame();
    auto player = sw.connectPlayer();
    sw.addEvent(player, BUTTON_UP, 1);
    std::this_thread::sleep_for(5000ms);
    auto obj = sw.getObjects(player);
    for (auto o : obj) {
        std::cout << o->getId() << ": " << o->getCoordinates().x << " " << o->getCoordinates().y << std::endl;
    }
    std::this_thread::sleep_for(5000ms);
    auto player2 = sw.connectPlayer();
    sw.addEvent(player2, COMMAND_SHOOT, 1);
    sw.addEvent(player, BUTTON_UP, 0);
    std::this_thread::sleep_for(5000ms);
    auto obj2 = sw.getObjects(player);
    for (auto o : obj2) {
        std::cout << o->getId() << ": " << o->getCoordinates().x << " " << o->getCoordinates().y << std::endl;
    }
    sw.disconnectPlayer(player);
    sw.endGame();
}