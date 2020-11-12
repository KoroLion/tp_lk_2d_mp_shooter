#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;

#include "MockWorld.hpp"

TEST(BasicTest, ToDoTest) {
    MockWorld world;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
