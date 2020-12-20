/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_GAME_HPP_
#define SRC_CLIENT_INCLUDE_GAME_HPP_

#include <vector>

#include "SDL.h"
#include "World.hpp"
#include "Camera.hpp"
#include "include/common.hpp"
#include "TcpClient.hpp"


class Game {
 public:
    Game(const char* title, int width, int height);

    bool start();
    void stop() { this->isRunning = false; }

    ~Game();

 private:
    void handleEvent(SDL_Event*);
    void keyboardEvents();
    void update();
    void render();

    void netEventCallback(NetServerEventType, std::string);
    static DWORD WINAPI networkThreadLauncher(LPVOID);
    DWORD networkThread();

    void recieveJson(std::string message);
    void sendJson(ClientCommands::ClientCommands command, bool action);

    const char* title;
    int width, height;
    unsigned int time;

    TcpClient net_client;

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool isRunning;

    Player* player;
    World* world;
    Camera* camera;

    std::vector<SDL_Texture*> textures;
};

#endif  // SRC_CLIENT_INCLUDE_GAME_HPP_
