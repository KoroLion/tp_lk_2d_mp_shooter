/*
Copyright 2020 github.com/KoroLion, github.com/SergTyapkin, github.com/altanab
*/
#include <iostream>

#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <utility>
#include <map>

#include "include/TcpServer.hpp"
#include "include/utils.hpp"
#include "include/common.hpp"

#include "include/lib/nlohmann/json.hpp"
using json = nlohmann::json;

#include "include/ServerApp.hpp"

std::string ServerApp::_game_objects_to_json(const std::vector<std::shared_ptr<GameObject>>& game_objects) {
    json j, json_objects, json_obj;

    j["cmd"] = "objs";
    j["time"] = 0;

    for (auto obj: game_objects) {
        json_obj["objid"] = obj->getId();
        json_obj["tid"] = obj->getType();
        json_obj["x"] = obj->getX();
        json_obj["y"] = obj->getY();
        json_obj["rot"] = 0;
        json_obj["hp"] = 100;
        json_objects.push_back(json_obj);
    }

    j["arg"] = json_objects;

    return j.dump();
}

ServerApp::ServerApp(std::string bind_addr, int port) {
    world = std::make_unique<ServerWorld>();
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
        unsigned objid = world->connectPlayer();
        std::cout << "Player " << uid << " (" << objid << ")" << " connected!" << std::endl;

        json j, json_arg;
        json_arg["objid"] = objid;
        json_arg["tid"] = ActionType::NEW_SELF_ID;
        j["cmd"] = "act";
        j["time"] = 0;
        j["arg"] = json_arg;
        net_server->send(uid, j.dump());

        uid_to_objid.insert(std::make_pair(uid, objid));
    } else if (ev_type == NetEventType::RECEIVED) {
        std::cout << "Received from " << uid << ": " << data << std::endl;
    } else if (ev_type == NetEventType::DISCONNECTED) {
        unsigned objid = uid_to_objid[uid];
        std::cout << "Player " << uid << " (" << objid << ")" << " disconnected!" << std::endl;
        world->disconnectPlayer(objid);
        uid_to_objid.erase(uid);
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
            std::vector<std::shared_ptr<GameObject>> game_objects = world->getObjects(1);

            std::string data = _game_objects_to_json(game_objects);

            std::cout << data << std::endl;
            net_server->send_all(data);
        }
        sleep_ms(1000);
    }
}

void ServerApp::game_world() {
    world->startGame();
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
    world->endGame();

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
