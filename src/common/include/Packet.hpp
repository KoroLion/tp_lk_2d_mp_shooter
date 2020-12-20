#ifndef SRC_CHAT_MESSAGE_HPP_
#define SRC_CHAT_MESSAGE_HPP_

#include <string>

class Packet {
 public:
    enum { header_length = 4 };
    enum { max_body_length = 512 };

    Packet(): _body_length(0) {}
    Packet(std::string);

    std::string get_as_string() const {
        std::string s(_data + header_length, _body_length);
        return s;
    }
    const char* get_body() const { return _data + header_length; }
    char *get_body() { return _data + header_length; }

    const char* get_data() const { return _data; };
    char* get_data() { return _data; };

    size_t get_header_length() { return header_length; };
    size_t get_body_length() { return _body_length; };
    void set_body_length(size_t new_length);

    size_t size() const {
        return header_length + _body_length;
    }
    bool decode_header();
    void encode_header();
  
 private:
    char _data[header_length + max_body_length];
    size_t _body_length;
};

#endif // SRC_CHAT_MESSAGE_HPP_
