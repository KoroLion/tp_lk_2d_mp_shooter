/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#ifndef SRC_SERVER_INCLUDE_SERVERAPP_HPP_
#define SRC_SERVER_INCLUDE_SERVERAPP_HPP_

#include <vector>
#include <thread>
#include <memory>
#include <string>

#include "utils.hpp"
#include "ServerWorld.hpp"
#include "TcpServer.hpp"

#include "include/common.hpp"

class ServerApp {
 private:
    bool running = true;
    std::map<unsigned, unsigned> uid_to_objid;
    time_t _cur_time = 0;
    unsigned short _notify_delay;

    std::unique_ptr<ServerWorld> world;
    std::unique_ptr<TcpServer> net_server;

    std::thread net_handle_thread;
    std::thread net_notify_thread;
    std::thread game_world_thread;

    std::string _game_objects_to_json(const std::vector<std::shared_ptr<GameObject>>& game_objects);

    void net_event_callback(NetEventType::NetEventType ev_type, unsigned uid, std::string data);
    void net_handle();
    void net_notify();
    void game_world();
    void handle_cmd();
 public:
    ServerApp(int port, int notify_rate);
    ~ServerApp() {}

    void stop();
    int start();
};

#endif  // SRC_SERVER_INCLUDE_SERVERAPP_HPP_
