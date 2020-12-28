/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/

#ifndef SRC_CLIENT_INCLUDE_GAME_HPP_
#define SRC_CLIENT_INCLUDE_GAME_HPP_

#include <vector>

#include "SDL.h"
#include "SDL_TTF.h"
#include "World.hpp"
#include "Camera.hpp"
#include "Buttons.hpp"
#include "include/common.hpp"
#include "TcpClient.hpp"

#define KEYS_COUNT    5
#define BUTTONS_COUNT 3

enum gamemodes {
    MENU,
    PLAYING
};

class Game {
 public:
    Game(const char* title, int width, int height, const std::string &IP, const std::string &port);

    bool start();
    void stop() {isRunning = false;}
    void reconnect(HANDLE& ht);

    ~Game();

 private:
    void renderBg(SDL_Renderer* renderer, SDL_Texture* texture);
    void handleEvent(SDL_Event*);
    void keyboardEvents();
    void updateMenu();
    void renderMenu();
    void update();
    void render();

    void netEventCallback(NetEventType::NetEventType, std::string);
    static DWORD WINAPI networkThreadLauncher(LPVOID);
    DWORD networkThread();

    void setPlayerId(int id);

    void recieveJson(std::string message);
    void sendJson(ClientCommands::ClientCommands command, int value);


    const char* title;
    int width, height;
    time_t time;
    std::string IP, port;

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool isRunning;
    bool isInConnectProcess;
    bool wantReconnect;

    int playerId;
    Player* player;
    World* world;
    Camera* camera;

    int gamemode;

    bool keys[KEYS_COUNT];
    bool buttons[BUTTONS_COUNT];

    TcpClient* net_client;
    std::vector<SDL_Texture*> textures;
    std::vector<TTF_Font*> fonts;

    std::vector<Button*> menuButtons;

    std::string menuConnectText;
    std::vector<std::pair<const char*, time_t>> chatMesages;
};

#endif // SRC_CLIENT_INCLUDE_GAME_HPP_
