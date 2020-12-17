#ifndef SRC_INCLUDE_SERVERAPP_HPP_
#define SRC_INCLUDE_SERVERAPP_HPP_

#include <iostream>

#include <vector>
#include <string>
#include <sstream>
#include <thread>

#include "utils.hpp"
#include "World.hpp"
#include "TcpServer.hpp"
#include "include/common.hpp"

std::string game_objects_to_json(const std::vector<GameObject>& game_objects) {
    std::stringstream ss;
    ss << "[";
    for (auto itr = game_objects.begin(); itr != game_objects.end(); itr++) {
        ss << "{";
        ss << "\"typeId\": " << itr->get_type_id() << ", ";
        ss << "\"x\": " << itr->get_x() << ", ";
        ss << "\"y\": " << itr->get_y();
        ss << "}";
        if (itr != (game_objects.end() - 1)) {
            ss << ", ";
        }
    }
    ss << "]";

    return ss.str();
}

class ServerApp {
 private:
    bool running = true;

    std::unique_ptr<World> world;
    std::unique_ptr<TcpServer> net_server;

    std::thread net_handle_thread;
    std::thread net_notify_thread;
    std::thread game_world_thread;
 public:
    ServerApp(std::string bind_addr, int port) {
        world = std::make_unique<World>();
        net_server = std::make_unique<TcpServer>(
            port,
            std::bind(
                &ServerApp::net_event_callback,
                this,
                std::placeholders::_1,
                std::placeholders::_2,
                std::placeholders::_3
            )
        );
    }
    ~ServerApp() {
    }

    void net_event_callback(NetServerEventType ev_type, unsigned uid, std::string data) {
        if (ev_type == CONNECTED) {
            std::cout << "Player " << uid << " connected!" << std::endl;
        } else if (ev_type == MESSAGE) {
            std::cout << uid << ": " << data << std::endl;
        } else if (ev_type == DISCONNECTED) {
            std::cout << "Player " << uid << " disconnected!" << std::endl;
        }
    }

    void net_handle() {
        net_server->start();
    }

    void net_notify() {
        while (!net_server->is_running()) {
            sleep_ms(50);
        }  // waiting for server to start

        while (net_server->is_running()) {
            if (net_server->get_players_amount()) {
                // todo: check for race condition!!!
                const std::vector<GameObject>& game_objects = world->get_game_objects(1);

                std::string data = game_objects_to_json(game_objects);

                std::cout << data << std::endl;
                net_server->send_all(data);
            }
            sleep_ms(1000);
        }
    }

    void game_world() {
        world->start();
    }

    void handle_cmd() {
        std::string command;
        while (this->running) {
            std::cin >> command;
            // todo: improve command parsing
            if (command == "stop") {
                std::cout << "Shutting down server..." << std::endl;
                stop();
            } else if (command == "online") {
                std::cout << net_server->get_players_amount() << " players are online." << std::endl;
            } else {
                std::cout << "Unknown command!" << std::endl;
            }
        }
    }

    void stop() {
        std::cout << "Stopping network..." << std::endl;
        net_server->stop();

        std::cout << "Stopping world..." << std::endl;
        world->stop();

        running = false;
    }

    int start() {
        net_handle_thread = std::thread(&ServerApp::net_handle, this);
        net_notify_thread = std::thread(&ServerApp::net_notify, this);
        game_world_thread = std::thread(&ServerApp::game_world, this);

        handle_cmd();

        net_handle_thread.join();
        net_notify_thread.join();
        game_world_thread.join();

        return 0;
    }
};

#endif  // SRC_INCLUDE_SERVERAPP_HPP_
