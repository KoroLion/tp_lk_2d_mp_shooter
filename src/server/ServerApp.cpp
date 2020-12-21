/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include <iostream>

#include <vector>
#include <string>
#include <sstream>
#include <thread>

#include "include/MockWorld.hpp"
#include "include/TcpServer.hpp"
#include "include/utils.hpp"
#include "include/common.hpp"

#include "include/lib/nlohmann/json.hpp"
using json = nlohmann::json;

#include "include/ServerApp.hpp"

std::string ServerApp::_game_objects_to_json(const std::vector<GameObject>& game_objects) {
    json j, json_objects, json_obj;

    j["cmd"] = "objs";

    for (auto itr = game_objects.begin(); itr != game_objects.end(); itr++) {
        json_obj["tid"] = itr->get_type_id();
        json_obj["x"] = itr->get_x();
        json_obj["y"] = itr->get_y();
        json_objects.push_back(json_obj);
    }

    j["arg"] = json_objects;

    return j.dump();
}

ServerApp::ServerApp(std::string bind_addr, int port) {
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

void ServerApp::net_event_callback(NetEventType::NetEventType ev_type, unsigned uid, std::string data) {
    if (ev_type == NetEventType::CONNECTED) {
        std::cout << "Player " << uid << " connected!" << std::endl;
    } else if (ev_type == NetEventType::RECEIVED) {
        std::cout << uid << ": " << data << std::endl;
    } else if (ev_type == NetEventType::DISCONNECTED) {
        std::cout << "Player " << uid << " disconnected!" << std::endl;
    }
}

void ServerApp::net_handle() {
    net_server->start();
}

void ServerApp::net_notify() {
    while (!net_server->is_running()) {
        sleep_ms(50);
    }  // waiting for server to start

    while (net_server->is_running()) {
        if (net_server->get_players_amount()) {
            // todo: check for race condition!!!
            const std::vector<GameObject>& game_objects = world->get_game_objects(1);

            std::string data = _game_objects_to_json(game_objects);

            std::cout << data << std::endl;
            net_server->send_all(data);
        }
        sleep_ms(1000);
    }
}

void ServerApp::game_world() {
    world->start();
}

void ServerApp::handle_cmd() {
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

void ServerApp::stop() {
    std::cout << "Stopping network..." << std::endl;
    net_server->stop();

    std::cout << "Stopping world..." << std::endl;
    world->stop();

    running = false;
}

int ServerApp::start() {
    net_handle_thread = std::thread(&ServerApp::net_handle, this);
    net_notify_thread = std::thread(&ServerApp::net_notify, this);
    game_world_thread = std::thread(&ServerApp::game_world, this);

    handle_cmd();

    net_handle_thread.join();
    net_notify_thread.join();
    game_world_thread.join();

    return 0;
}
