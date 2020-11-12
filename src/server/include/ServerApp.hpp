#ifndef SRC_INCLUDE_SERVERAPP_HPP_
#define SRC_INCLUDE_SERVERAPP_HPP_

#include <vector>
#include <string>
#include <thread>

#include "GameServer.hpp"

class ServerApp {
 private:
    World *w;
    GameServer *gs;

    std::thread gs_thread;
    std::thread w_thread;
 public:
    ServerApp() {
        w = new World;
        gs = new GameServer("0.0.0.0", 23000, w);
    }
    ~ServerApp() {
        delete gs;
    }
    void gs_serve() {
        gs->start();
    }

    int start() {
        gs_thread = std::thread(&ServerApp::gs_serve, this);
        gs_thread.join();

        return 0;
    }
};

#endif  // SRC_INCLUDE_SERVERAPP_HPP_
