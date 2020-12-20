#ifndef SRC_CHAT_MESSAGE_HPP_
#define SRC_CHAT_MESSAGE_HPP_

#include <string>

class Packet {
 public:
    enum { header_length = 4 };
    enum { max_body_length = 512 };

    Packet(): body_length_(0) {}
    Packet(std::string);

    std::string get_as_string() const {
        std::string s(data_ + header_length, body_length_);
        return s;
    }
    const char* get_body() const { return data_ + header_length; }
    char *get_body() { return data_ + header_length; }

    const char* get_data() const { return data_; };
    char* get_data() { return data_; };

    size_t get_header_length() { return header_length; };
    size_t get_body_length() { return body_length_; };
    void set_body_length(size_t new_length);

    size_t size() const {
        return header_length + body_length_;
    }
    bool decode_header();
    void encode_header();
 private:
    char data_[header_length + max_body_length];
    size_t body_length_;
};

#endif // SRC_CHAT_MESSAGE_HPP_
