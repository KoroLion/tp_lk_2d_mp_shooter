#ifndef SRC_INCLUDE_SERVERAPP_HPP_
#define SRC_INCLUDE_SERVERAPP_HPP_

#include <vector>
#include <string>

#include "GameServer.hpp"

class ServerApp {
 private:
    GameServer *gs;
 public:
    ServerApp() {
        gs = new GameServer("0.0.0.0", 23000);
    }
    ~ServerApp() {
        delete gs;
    }

    int start() {
        return 0;
    }
    void stop() {}
};

#endif  // SRC_INCLUDE_SERVERAPP_HPP_
