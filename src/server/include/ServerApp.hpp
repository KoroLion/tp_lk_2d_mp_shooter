#ifndef SRC_INCLUDE_SERVERAPP_HPP_
#define SRC_INCLUDE_SERVERAPP_HPP_

#include <vector>
#include <string>
#include <thread>

#include "GameServer.hpp"

class ServerApp {
 private:
    std::shared_ptr<World> w;
    std::unique_ptr<GameServer> gs;

    std::thread gs_thread;
    std::thread w_thread;
 public:
    ServerApp(std::string bind_addr, int port) {
        w = std::make_shared<World>();
        gs = std::make_unique<GameServer>(bind_addr, port, w);
    }
    ~ServerApp() {
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
