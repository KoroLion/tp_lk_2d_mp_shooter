#include "gtest/gtest.h"

#include "include/Packet.hpp"
#include <cstring>

TEST(PacketTest, PacketEncode) {
    Packet packet("wolf&lion");

    EXPECT_EQ(packet.get_as_string(), "wolf&lion");
    EXPECT_EQ(packet.get_header_length(), 4);
    EXPECT_EQ(packet.get_body_length(), 9);
    EXPECT_EQ(packet.size(), packet.get_header_length() + packet.get_body_length());
}

TEST(PacketTest, PacketDecode) {
    Packet packet;

    EXPECT_EQ(packet.get_as_string(), "");
    EXPECT_EQ(packet.get_header_length(), 4);
    EXPECT_EQ(packet.get_body_length(), 0);
    EXPECT_EQ(packet.size(), packet.get_header_length() + packet.get_body_length());

    char header[] = "   9";
    std::memcpy(packet.get_data(), header, 4);
    packet.decode_header();

    char data[] = "wolf&lion";
    std::memcpy(packet.get_body(), data, 9);

    EXPECT_EQ(packet.get_body_length(), 9);
    EXPECT_EQ(packet.get_as_string(), "wolf&lion");
}
