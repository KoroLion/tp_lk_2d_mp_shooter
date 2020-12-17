#include <cstring>  // for memcpy

#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#include "include/Packet.hpp"

Packet::Packet(std::string data) {
    body_length_ = data.length();
    std::memcpy(data_ + header_length, data.data(), body_length_);
    encode_header();
}

void Packet::set_body_length(size_t new_length) {
    body_length_ = new_length;
    if (body_length_ > max_body_length) {
        body_length_ = max_body_length;
    }
}

bool Packet::decode_header() {
    std::string s(data_, header_length);
    body_length_ = std::atoi(s.c_str());
    if (body_length_ > max_body_length) {
        body_length_ = 0;
        return false;
    }
    return true;
}

void Packet::encode_header() {
    std::stringstream buffer;
    buffer << std::setw(4) << static_cast<int>(body_length_);
    std::memcpy(data_, buffer.str().data(), header_length);
}
