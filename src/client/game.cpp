/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/
#include <iostream>
#include <math.h>
#include <vector>

#include "SDL.h"
#include "SDL_TTF.h"
#include "lib/json.hpp"

#include "include/Game.hpp"
#include "include/World.hpp"
#include "include/Camera.hpp"
#include "include/Colors.hpp"
#include "include/Entities.hpp"
#include "include/Buttons.hpp"
#include "include/common.hpp"
#include "include/TcpClient.hpp"
//using json = nlohmann::json;

#define WINDOW_X_INIT 300
#define WINDOW_Y_INIT 300
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

#define FPS         60
#define FPS_IN_MENU 30

#define SEEK_ROTATION true
#define USE_MOUSE_FOR_ROTATE true
#define MOUSE_SENSIVITY 0.1

enum textures_id {
    BOX_TEXTURE_ID,
    BG_TEXTURE_ID,
    BG_VIGNETTE_TEXTURE_ID,
    PLAYER_TEXTURE_ID,
    BULLET_TEXTURE_ID,
    LIGHT_TRASSER_TEXTURE_ID,
    STRAIGHT_TRASSER_TEXTURE_ID,
    BG_MENU_TEXTURE_ID,
    BUTTON_HEXAGON_TEXTURE_ID
};

enum fonts_id {
    MENU_CONNECTING_FONT_ID,
    MENU_BUTTONS_FONT_ID,
    CHAT_MESSAGES_FONT_ID
};

enum keycodes{
    KEYCODE_W,
    KEYCODE_A,
    KEYCODE_S,
    KEYCODE_D,
    KEYCODE_R
};

enum buttoncodes{
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_WHEEL
};

extern void renderText(SDL_Renderer* renderer, const char* text,
        int x, int y, TTF_Font* font, Uint8 r, Uint8 g, Uint8 b, Uint8 a); // in Buttons.cpp

void Game::renderBg(SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Rect rect{0,0, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

SDL_Texture* loadTexture(const char* imgName, SDL_Renderer* renderer, SDL_Surface* win_surf, Uint8 r = -1, Uint8 g = -1, Uint8 b = -1) {
    SDL_Surface* tmp_surf = SDL_LoadBMP(imgName);
    if (tmp_surf == NULL) {
        SDL_Log("%s%s\n", "Can't load surface: ", SDL_GetError());
        return NULL;
    }
    if (r != -1)
        SDL_SetColorKey(tmp_surf, SDL_TRUE, SDL_MapRGB(tmp_surf->format, r,g,b));
    /*
    tmp_surf = SDL_ConvertSurface(tmp_surf, win_surf->format, 0);
    if (tmp_surf == NULL) {
        SDL_Log("%s%s\n", "Can't convert to new format: ", SDL_GetError());
        return NULL;
    }
    */
    SDL_Texture* tmp_texture = SDL_CreateTextureFromSurface(renderer, tmp_surf);
    if (tmp_texture == NULL) {
        SDL_Log("%s%s\n", "Can't conver surf to texture: ", SDL_GetError());
        return NULL;
    }
    return tmp_texture;
}

Game::Game(const char* _title, int _width, int _height, const std::string &_IP, const std::string &_port):
           title(_title), width(_width), height(_height), IP(_IP), port(_port),
           isRunning(false), isInConnectProcess(false), wantReconnect(false), playerId(-1), player(NULL), gamemode(MENU) {

    /** Create TCPClient **/
    net_client = new TcpClient(IP, port, std::bind(netEventCallback, this, std::placeholders::_1, std::placeholders::_2));

    /** Init libraries **/
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("%s%s\n", "Can't init SDL: ", SDL_GetError());
        return;
    }
    if (TTF_Init()) {
        SDL_Log("%s%s\n", "Can't init SDL_ttf: ", TTF_GetError());
        return;
    }

    /** Create window **/
    if ((window = SDL_CreateWindow(title, WINDOW_X_INIT, WINDOW_Y_INIT, width, height, SDL_WINDOW_OPENGL)) == NULL) { // | SDL_WINDOW_INPUT_GRABBED
        SDL_Log("%s%s\n", "Can't create window: ", SDL_GetError());
        return;
    }

    /** Create renderer **/
    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
        SDL_Log("%s%s\n", "Can't create renderer: ", SDL_GetError());
        return;
    }

    /** Load textures **/
    SDL_Surface* win_surf = SDL_GetWindowSurface(window);
    static const char* textureNames [] = {"res/textures/box.bmp", "res/textures/bg_1.bmp", "res/textures/bg_vignette.bmp", "res/textures/player.bmp",
                                           "res/textures/bullet.bmp", "res/textures/light_trasser.bmp", "res/textures/straight_trasser.bmp", "res/textures/bg_menu.bmp",
                                           "res/textures/hexagon_button.bmp"};
    for (int i = 0; i < 9; i++)
        textures.push_back(loadTexture(textureNames[i], renderer, win_surf, WHITE_RGB));
    // --- modding textures ---
    SDL_SetTextureAlphaMod(textures[BG_VIGNETTE_TEXTURE_ID], 0xCC);
    //SDL_SetTextureBlendMode(textures[BG_VIGNETTE_TEXTURE_ID], SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(textures[BG_TEXTURE_ID], CYAN_RGB);

    /** Load fonts **/
    static const char* fontNames[] = {"res/fonts/metatron.ttf", "res/fonts/metatron.ttf", "res/fonts/FreeSans.ttf"};
    const int fontSizes[] = {height/20, height/40, 14};
    for (int i = 0; i < 3; i++)
        fonts.push_back(TTF_OpenFont(fontNames[i], fontSizes[i]));

    /** Fill key arrays **/
    for (int i = 0; i < KEYS_COUNT; i++)
        keys[i] = false;
    for (int i = 0; i < BUTTONS_COUNT; i++)
        buttons[i] = false;

    /** Create buttons **/
    menuButtons.push_back(new RectangleButton(width/4, height/3*2, width/4, height/8, 0, textures[BUTTON_HEXAGON_TEXTURE_ID], textures[BG_VIGNETTE_TEXTURE_ID], textures[BOX_TEXTURE_ID],
                                            fonts[MENU_BUTTONS_FONT_ID], "Retry", CYAN_RGB, 0xCC, [this](){this->wantReconnect = true;}));
    menuButtons.push_back(new RectangleButton(width/4*3, height/3*2, width/4, height/8, 0, textures[BUTTON_HEXAGON_TEXTURE_ID], textures[BG_VIGNETTE_TEXTURE_ID], textures[BOX_TEXTURE_ID],
                                            fonts[MENU_BUTTONS_FONT_ID], "Exit", CYAN_RGB, 0xCC, [this](){this->isRunning = false;}));

    /** Create objects **/
    world = new World(1000, 1000, textures[BG_TEXTURE_ID], textures[BG_VIGNETTE_TEXTURE_ID]);

    /*player = new Player(200,200,2, 40,40, 0, textures[PLAYER_TEXTURE_ID], 5);
    world->addEntity(0, player);

    for (int i = 1; i < 1+5; i++) {
        world->addEntity(i, new Obstacle(0,0,0, 0,0, 0, textures[BOX_TEXTURE_ID]));
    }

    std::map<int, Entity*> targetEntities;
    targetEntities.insert(std::pair<const int, Entity*>(1, new Obstacle(50,120,1, 50,50, 30, NULL)));
    targetEntities.insert(std::pair<const int, Entity*>(2, new Obstacle(60,30,1, 60,60, -20, NULL)));
    targetEntities.insert(std::pair<const int, Entity*>(3, new Obstacle(300,250,2, 100,200, 0, NULL)));
    targetEntities.insert(std::pair<const int, Entity*>(4, new Obstacle(250,20,3, 100,200, 90, NULL)));
    targetEntities.insert(std::pair<const int, Entity*>(5, new Obstacle(20,400,5, 80,100, 20, NULL)));

    world->setTarget(targetEntities, 0);

    targetEntities.clear();
    targetEntities.insert(std::pair<const int, Entity*>(1, new Obstacle(50,120,1, 50,50, 30, NULL)));
    targetEntities.insert(std::pair<const int, Entity*>(2, new Obstacle(60,30,1, 60,60, 200, NULL)));
    targetEntities.insert(std::pair<const int, Entity*>(3, new Obstacle(300,250,2, 100,200, 0, NULL)));
    targetEntities.insert(std::pair<const int, Entity*>(4, new Obstacle(250,20,3, 100,200, 90, NULL)));
    targetEntities.insert(std::pair<const int, Entity*>(5, new Obstacle(150,200,5, 80,100, 20, NULL)));

    world->setTarget(targetEntities, 10*1000);

    */
    camera = new Camera(width/2, height/2, 10, 60, WINDOW_WIDTH, WINDOW_HEIGHT, 0, world, player, SEEK_ROTATION);

    //world->addAnimation(new LightTrasser(player, player->getX(), player->getY(), player->getWidth()/2, player->getRotation(), textures[LIGHT_TRASSER_TEXTURE_ID]));
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

DWORD WINAPI Game::networkThreadLauncher(LPVOID p) {
    return ((Game*)p)->networkThread();
}

DWORD Game::networkThread() {
    try {
        if (!isInConnectProcess) {
            SDL_Log("%s\n", "Trying to connect...");
            menuConnectText = "Connecting...";
            isInConnectProcess = true;
            net_client->connect();
            SDL_Log("%s\n", "Disconnected from server");
            menuConnectText = "Disconnected";
            isInConnectProcess = false;
        }
    } catch (const std::exception &e) {
        SDL_Log("%s\n", "WARNING: Failed to connect!");
        menuConnectText = "Connection  failed";
        isInConnectProcess = false;
        //return 1;
    }
    return 0;
}

void Game::netEventCallback(NetEventType::NetEventType evType, std::string data) {
    if (evType == NetEventType::CONNECTED) {
        SDL_Log("%s\n", "INFO: Connected!");
    } else if (evType == NetEventType::RECEIVED) {
        SDL_Log("%s%s\n", "RECEIVED: ", "*big json file*"); // data.c_str());
        recieveJson(data);
    } else if (evType == NetEventType::DISCONNECTED) {
        SDL_Log("%s\n", "INFO: Disconnected!");
        SDL_ShowCursor(SDL_ENABLE);
        player = NULL;
        setPlayerId(-1);
        world->clearAll();
        camera->setTarget(NULL);
        gamemode = MENU;
    }
}

void Game::reconnect(HANDLE &ht) {
    if (isInConnectProcess)
        return;
    //WaitForSingleObject(ht, INFINITE);
    CloseHandle(ht);

    delete net_client;
    net_client = new TcpClient(IP, port, std::bind(netEventCallback, this, std::placeholders::_1, std::placeholders::_2));

    DWORD tid = 0;
    ht = CreateThread(NULL, 0, networkThreadLauncher, this, 0, &tid);
}

bool Game::start() {
    isRunning = true;
    DWORD tid = 0;
    HANDLE ht = CreateThread(NULL, 0, networkThreadLauncher, this, 0, &tid);
    if (ht == NULL) {
        SDL_Log("%s\n", "ERROR: Unable to start thread!");
        throw std::exception();
    }

    SDL_Log("%s\n", "Game started");
    time = 0;
    //main loop
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            handleEvent(&event);
        keyboardEvents();

        switch (gamemode) {
        case MENU:
            if (net_client->is_connected()) {
                if (SEEK_ROTATION && USE_MOUSE_FOR_ROTATE) {
                    //SDL_SetRelativeMouseMode(SDL_TRUE);
                    SDL_ShowCursor(SDL_DISABLE);
                }
                time = 0;
                gamemode = PLAYING;
                break;
            }
            updateMenu();
            renderMenu();
            SDL_RenderPresent(renderer);

            if (wantReconnect) {
                wantReconnect = false;
                reconnect(ht);
            }
            time += 1000/FPS_IN_MENU;
            SDL_Delay(1000/FPS_IN_MENU);
            break;
        case PLAYING:
            SDL_SetRenderDrawColor(renderer, WHITE_RGBA);
            SDL_RenderClear(renderer);
            update();
            render();
            SDL_RenderPresent(renderer);

            time += 1000/FPS;
            SDL_Delay(1000/FPS);
            break;
        }
    }

    net_client->close();
    WaitForSingleObject(ht, INFINITE);
    CloseHandle(ht);

    return 0;
}

void Game::renderMenu() {
    renderBg(renderer, textures[BG_MENU_TEXTURE_ID]);
    renderText(renderer, menuConnectText.c_str(), width/2, height/2, fonts[MENU_CONNECTING_FONT_ID], CYAN_RGBA);
    for(Button* button: menuButtons) {
        button->render(renderer);
    }
}

void Game::updateMenu() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    for(Button* button: menuButtons) {
        button->update(mouseX, mouseY, buttons[BUTTON_LEFT]);
    }
}

void Game::render() {
    camera->render(renderer);
    static const int BULLET_SIZE = 15;
    if (player) {
        for (int i = 0; i < player->getAmmo(); i++) {
            SDL_Rect rect {BULLET_SIZE + i*BULLET_SIZE, BULLET_SIZE, BULLET_SIZE, BULLET_SIZE/2};
            SDL_RenderCopyEx(renderer, textures[BULLET_TEXTURE_ID], NULL, &rect, -75, NULL, SDL_FLIP_NONE);
        }
    }
    int i = 0;
    int alpha;
    for (auto message: chatMesages) {
        if (message.second >= 1000)
            alpha = 0xFF;
        else
            alpha = 0xFF * message.second / 1000;
        renderText(renderer, message.first, width - 80, 20 + i*15, fonts[CHAT_MESSAGES_FONT_ID], CYAN_RGB, alpha);
        i++;
    }
}

void Game::update() {
    world->update(time, player);
    camera->update();
    if (player) {
        player->updateTime(1000/FPS);
        if (!world->isInEntities(player))
            net_client->close();
    }


    Entity* tmp;
    if ((tmp = world->getEntity(playerId)) != NULL) {
        player = (Player*)tmp;
        camera->setTarget(player);
    }

    for (auto itr = chatMesages.begin(); itr != chatMesages.end(); itr++) {
        itr->second -= 1000/FPS;
        if (itr->second <= 0)
            chatMesages.erase(itr--);
    }
}

void Game::setPlayerId(int id) {
    playerId = id;
}

void Game::handleEvent(SDL_Event* event) {
    if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE ||
        (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE))
        stop();

    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {
        case SDLK_w:
            if (!keys[KEYCODE_W])
                sendJson(ClientCommands::MOVE_UP, true);
            keys[KEYCODE_W] = true;
            break;
        case SDLK_a:
            if (!keys[KEYCODE_A])
                sendJson(ClientCommands::MOVE_LEFT, true);
            keys[KEYCODE_A] = true;
            break;
        case SDLK_s:
            if (!keys[KEYCODE_S])
                sendJson(ClientCommands::MOVE_DOWN, true);
            keys[KEYCODE_S] = true;
            break;
        case SDLK_d:
            if (!keys[KEYCODE_D])
                sendJson(ClientCommands::MOVE_RIGHT, true);
            keys[KEYCODE_D] = true;
            break;
        case SDLK_r:
            if (player)
                player->startReload();
            if (!keys[KEYCODE_R])
                sendJson(ClientCommands::RELOAD, true);
            keys[KEYCODE_R] = true;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event->key.keysym.sym) {
        case SDLK_w:
            sendJson(ClientCommands::MOVE_UP, false);
            keys[KEYCODE_W] = false;
            break;
        case SDLK_a:
            sendJson(ClientCommands::MOVE_LEFT, false);
            keys[KEYCODE_A] = false;
            break;
        case SDLK_s:
            sendJson(ClientCommands::MOVE_DOWN, false);
            keys[KEYCODE_S] = false;
            break;
        case SDLK_d:
            sendJson(ClientCommands::MOVE_RIGHT, false);
            keys[KEYCODE_D] = false;
            break;
        case SDLK_r:
            keys[KEYCODE_R] = false;
            break;
        }
        break;
    case SDL_MOUSEMOTION:
        if (USE_MOUSE_FOR_ROTATE == false)
            return;
        if (gamemode != PLAYING)
            return;
        if (!player)
            return;

        int mouseX, mouseY;
        if (SEEK_ROTATION) {
            //SDL_GetRelativeMouseState(&mouseX, &mouseY);
            SDL_GetMouseState(&mouseX, &mouseY);
            mouseX -= width/2;
            SetCursorPos(WINDOW_X_INIT + width/2, WINDOW_Y_INIT + height/2);
            player->rotateRelative(mouseX * MOUSE_SENSIVITY);
            //if ((time % 1000 < 200) && (player != NULL)) {
                sendJson(ClientCommands::ROTATE, player->getRotation());
            //}
        } else {
            SDL_GetMouseState(&mouseX, &mouseY);
            player->setRotation(getAngle(width/2, height/2, mouseX, mouseY));
            //if ((time % 1000 < 200) && (player != NULL)) {
                sendJson(ClientCommands::ROTATE, getAngle(width/2, height/2, mouseX, mouseY));
            //}
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        switch (event->button.button) {
        case SDL_BUTTON_LEFT:
            buttons[BUTTON_LEFT] = true;
            chatMesages.push_back(std::pair<const char*, time_t>("Shoot!", 2000));
            if (!player)
                return;
            if (!player->isReloaded())
                return;
            player->reduceAmmo(1);
            //player->shoot(world, textures[BULLET_TEXTURE_ID], textures[LIGHT_TRASSER_TEXTURE_ID], textures[STRAIGHT_TRASSER_TEXTURE_ID]);
            if (player->getAmmo() > 0) {
                sendJson(ClientCommands::ROTATE, player->getRotation());
                sendJson(ClientCommands::SHOOT, true);
            }
            break;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        switch (event->button.button) {
        case SDL_BUTTON_LEFT:
            buttons[BUTTON_LEFT] = false;
            break;
        }
        break;
    }
}

void Game::keyboardEvents() {
    if (!player)
        return;

    if (SEEK_ROTATION || !USE_MOUSE_FOR_ROTATE) {
        if (keys[KEYCODE_W])
            player->moveRelative(0);
        if (keys[KEYCODE_A]) {
            if (USE_MOUSE_FOR_ROTATE)
                player->moveRelative(-90);
            else
                player->rotateRelative(-10);
        }
        if (keys[KEYCODE_S])
            player->moveRelative(180);
        if (keys[KEYCODE_D]) {
            if (USE_MOUSE_FOR_ROTATE)
                player->moveRelative(90);
            else
                player->rotateRelative(10);
        }
    } else {
        if (keys[KEYCODE_W])
            player->moveAbsolute(0, -player->getSpeed());
        if (keys[KEYCODE_A])
            player->moveAbsolute(-player->getSpeed(), 0);
        if (keys[KEYCODE_S])
            player->moveAbsolute(0, player->getSpeed());
        if (keys[KEYCODE_D])
            player->moveAbsolute(player->getSpeed(), 0);
    }
}

void Game::recieveJson(std::string message) {
    auto j = nlohmann::json::parse(message);
    std::string cmnd;
    j.at("cmd").get_to(cmnd);
    SDL_Log("Parse: Cmnd: %s", cmnd.c_str());
    if (cmnd == "objs") {
        std::map<int, Entity*> newTarget;
        for (auto ent: j["arg"]) {
            //SDL_Log("Id: %d, Type: %d, Coords: (%d %d), Grad: %d, Hp: %d\n",
            //        (int)ent["objid"], (int)ent["tid"], (int)ent["x"], (int)ent["y"], (int)ent["rot"], (int)ent["hp"]);
            bool found = (world->getEntity(ent["objid"]) != NULL);
            switch ((int)ent["tid"]) {
            case EntityType::PLAYER:
                newTarget.insert(std::pair<const int, Entity*>(ent["objid"], new Player(ent["x"], ent["y"], 1, 40,40, ent["rot"], ent["hp"], NULL, 5)));
                if (!found) {
                    world->addEntity(ent["objid"], new Player(ent["x"], ent["y"], 1, 40, 40, ent["rot"], ent["hp"], textures[PLAYER_TEXTURE_ID], 5));
                }
                break;
            case EntityType::BULLET:
                newTarget.insert(std::pair<const int, Entity*>(ent["objid"], new Bullet(ent["x"], ent["y"], 1, 10, 5, ent["rot"], ent["hp"], NULL, 12)));
                if (!found) {
                    Entity* bul;
                    world->addEntity(ent["objid"], bul = new Bullet(ent["x"], ent["y"], 1, 10, 5, ent["rot"], ent["hp"], textures[BULLET_TEXTURE_ID], 12));
                    world->addAnimation(new LightTrasser(bul, ent["x"], ent["y"], 12, ent["rot"], textures[LIGHT_TRASSER_TEXTURE_ID]));
                }
                break;
            case EntityType::BOX_SMALL:
                newTarget.insert(std::pair<const int, Entity*>(ent["objid"], new Obstacle(ent["x"], ent["y"], 1,  50, 50, ent["rot"], ent["hp"], NULL)));
                if (!found) {
                    world->addEntity(ent["objid"], new Obstacle(ent["x"], ent["y"], 1,  50, 50, ent["rot"], ent["hp"], textures[BOX_TEXTURE_ID]));
                }
                break;
            case EntityType::BOX_BIG:
                newTarget.insert(std::pair<const int, Entity*>(ent["objid"], new Obstacle(ent["x"], ent["y"], 2, 100,100, ent["rot"], ent["hp"], NULL)));
                if (!found) {
                    world->addEntity(ent["objid"], new Obstacle(ent["x"], ent["y"], 2, 100,100, ent["rot"], ent["hp"], textures[BOX_TEXTURE_ID]));
                }
                break;
            }
        }
        world->setTarget(newTarget, j["time"]);
        SDL_Log("Time: %d", (int)j["time"]);
    } else if (cmnd == "act") {
        switch ((int)j["arg"]["tid"]) {
        case ActionType::NEW_SELF_ID:
            setPlayerId(j["arg"]["objid"]);
            SDL_Log("New player ID: %d", (int)j["arg"]["objid"]);
            break;
        case ActionType::NEW_OBJECT:
            if (j["arg"]["arg"] == EntityType::PLAYER) {
                SDL_Log("New connected player: %d", (int)j["arg"]["objid"]);
                char* mes = new char[30];
                sprintf(mes, "%s%d", "Connect player", (int)j["arg"]["objid"]);
                chatMesages.push_back(std::pair<const char*, time_t>(mes, 10000));
            }
            break;
        case ActionType::DESTROYED:
            if (j["arg"]["arg"] == EntityType::PLAYER) {
                SDL_Log("Disconnected player ID: %d", (int)j["arg"]["objid"]);
                char* mes = new char[30];
                sprintf(mes, "%s%d", "Disconnected player", (int)j["arg"]["objid"]);
                chatMesages.push_back(std::pair<const char*, time_t>(mes, 10000));
            }
            break;
        }
    }
}

void Game::sendJson(ClientCommands::ClientCommands command, int value) {
    if (!net_client->is_connected())
        return;
    nlohmann::json j;
    j["cmd"] = command;
    j["arg"] = value;
    net_client->send(j.dump());
    SDL_Log("SEND: %s", j.dump().c_str());
}
