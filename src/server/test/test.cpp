#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ServerWorld.hpp"
using namespace std::literals::chrono_literals;

TEST(BasicTest, TryTest) {
    ServerWorld sw;
    sw.startGame();
    sw.addEvent(0, PLAYER_CONNECTED, 1);
    sw.addEvent(6, BUTTON_UP, 1);
    std::this_thread::sleep_for(5000ms);
    auto obj = sw.getObjects(6);
    for (auto o : obj) {
        std::cout << o->getId() << ": " << o->getCoordinates().x << " " << o->getCoordinates().y << std::endl;
    }
    std::this_thread::sleep_for(5000ms);
    sw.addEvent(0, PLAYER_CONNECTED, 1);
    sw.addEvent(7, COMMAND_SHOOT, 1);
    std::this_thread::sleep_for(5000ms);
    sw.addEvent(6, BUTTON_UP, 0);
    std::this_thread::sleep_for(5000ms);
    auto obj2 = sw.getObjects(6);
    for (auto o : obj2) {
        std::cout << o->getId() << ": " << o->getCoordinates().x << " " << o->getCoordinates().y << std::endl;
    }
    sw.endGame();
}