#ifndef SRC_COMMON_HPP_
#define SRC_COMMON_HPP_

#include <string>
#include <functional>

enum NetServerEventType {
    CONNECTED,
    MESSAGE,
    DISCONNECTED
};

typedef std::function<void(NetServerEventType, unsigned, std::string)> net_event_callback;

#endif
