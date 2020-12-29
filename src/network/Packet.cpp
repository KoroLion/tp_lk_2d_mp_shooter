/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include <cstring>  // for memcpy

#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#include "include/Packet.hpp"

Packet::Packet(std::string data) {
    _body_length = data.length();
    std::memcpy(_data + header_length, data.data(), _body_length);
    encode_header();
}

void Packet::set_body_length(size_t new_length) {
    _body_length = new_length;
    if (_body_length > max_body_length) {
        _body_length = max_body_length;
    }
}

bool Packet::decode_header() {
    std::string s(_data, header_length);
    _body_length = std::stoi(s);
    if (_body_length > max_body_length) {
        _body_length = 0;
        return false;
    }
    return true;
}

void Packet::encode_header() {
    std::stringstream buffer;
    buffer << std::setw(4) << static_cast<int>(_body_length);
    std::memcpy(_data, buffer.str().data(), header_length);
}
