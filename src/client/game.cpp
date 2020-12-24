/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/
#include <iostream>
#include <math.h>
#include <vector>

#include "SDL.h"
#include "include/Game.hpp"
#include "include/World.hpp"
#include "include/Camera.hpp"
#include "include/Colors.hpp"
#include "include/Entities.hpp"
#include "include/common.hpp"
#include "include/TcpClient.hpp"
#include "lib/json.hpp"
//using json = nlohmann::json;

#define WINDOW_X_INIT 300
#define WINDOW_Y_INIT 300
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

#define FPS 60

#define SEEK_ROTATION true
#define USE_MOUSE_FOR_ROTATE true
#define MOUSE_SENSIVITY 0.1

#define BOX_TEXTURE_ID              0
#define BG_TEXTURE_ID               1
#define BG_VIGNETTE_TEXTURE_ID      2
#define PLAYER_TEXTURE_ID           3
#define BULLET_TEXTURE_ID           4
#define LIGHT_TRASSER_TEXTURE_ID    5
#define STRAIGHT_TRASSER_TEXTURE_ID 6

enum keycodes{
    KEYCODE_W,
    KEYCODE_A,
    KEYCODE_S,
    KEYCODE_D
};

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

Game::Game(const char* _title, int _width, int _height, const std::string &IP, const std::string &port): title(_title), width(_width), height(_height),
        playerId(-1), player(NULL),
        net_client(IP, port, std::bind(
            netEventCallback,
            this,
            std::placeholders::_1,
            std::placeholders::_2
        )) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("%s%s\n", "Can't init: ", SDL_GetError());
        return;
    }

    if ((window = SDL_CreateWindow(title, WINDOW_X_INIT, WINDOW_Y_INIT, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED)) == NULL) {
        SDL_Log("%s%s\n", "Can't create window: ", SDL_GetError());
        return;
    }

    if (SEEK_ROTATION && USE_MOUSE_FOR_ROTATE) {
        //SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_ShowCursor(SDL_DISABLE);
    }

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
        SDL_Log("%s%s\n", "Can't create renderer: ", SDL_GetError());
        return;
    }

    // --- loading textures ---
    SDL_Surface* win_surf = SDL_GetWindowSurface(window);
    std::vector<const char*> textureNames {"res/textures/box.bmp", "res/textures/bg_1.bmp", "res/textures/bg_vignette.bmp", "res/textures/player.bmp",
                                           "res/textures/bullet.bmp", "res/textures/light_trasser.bmp", "res/textures/straight_trasser.bmp"};
    for (const char* name: textureNames)
        textures.push_back(loadTexture(name, renderer, win_surf, WHITE_RGB));
    // --- modding textures ---
    SDL_SetTextureAlphaMod(textures[BG_VIGNETTE_TEXTURE_ID], 0xCC);
    //SDL_SetTextureBlendMode(textures[BG_VIGNETTE_TEXTURE_ID], SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(textures[BG_TEXTURE_ID], CYAN_RGB);

    for (int i = 0; i < KEYS_COUNT; i++) {
        keys[i] = false;
    }

    world = new World(WINDOW_WIDTH, WINDOW_HEIGHT, textures[BG_TEXTURE_ID], textures[BG_VIGNETTE_TEXTURE_ID]);

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
        net_client.connect();
    } catch (const std::exception &e) {
        SDL_Log("%s\n", "WARNING: Failed to connect!");
        return 1;
    }

    return 0;
}

void Game::netEventCallback(NetEventType::NetEventType evType, std::string data) {
    if (evType == NetEventType::CONNECTED) {
        SDL_Log("%s\n", "INFO: Connected!");
    } else if (evType == NetEventType::RECEIVED) {
        SDL_Log("%s%s\n", "RECEIVED: ", "*json file*"); //data.c_str());
        recieveJson(data);
    } else if (evType == NetEventType::DISCONNECTED) {
        SDL_Log("%s\n", "INFO: Disconnected!");
    }
}

bool Game::start() {
    DWORD tid = 0;
    HANDLE ht = CreateThread(NULL, 0, networkThreadLauncher, this, 0, &tid);
    if (ht == NULL) {
        SDL_Log("%s\n", "ERROR: Unable to start thread!");
        throw std::exception();
    }

    SDL_Log("%s\n", "Game started");
    isRunning = true;
    time = 0;

    // waiting for connection
    int wait_amount = 0;
    const int MAX_WAIT_AMOUNT = 3;
    while (!net_client.is_connected()) {
        if (wait_amount > MAX_WAIT_AMOUNT) {
            SDL_Log("%s\n", "ERROR: Unable to connect to server!");
            throw std::exception();
        }
        wait_amount++;
        SDL_Delay(500);
    }

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            handleEvent(&event);
        keyboardEvents();

        SDL_SetRenderDrawColor(renderer, WHITE_RGBA);
        SDL_RenderClear(renderer);
        update();
        render();
        SDL_RenderPresent(renderer);

        time += 1000/FPS;
        SDL_Delay(1000/FPS);
    }

    net_client.close();
    WaitForSingleObject(ht, INFINITE);
    CloseHandle(ht);

    return 0;
}

void Game::render() {
    camera->render(renderer);
}

void Game::update() {
    world->update(time, player);
    camera->update();

    Entity* tmp;
    if ((tmp = world->getEntity(playerId)) != NULL) {
        player = (Player*)tmp;
        camera->setTarget(player);
    }
}

void Game::setPlayerId(int id) {
    playerId = id;
}

void Game::handleEvent(SDL_Event* event) {
    if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE ||
        (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE))
        stop();

    if (!player)
        return;

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
        }
        break;
    case SDL_MOUSEMOTION:
        if (USE_MOUSE_FOR_ROTATE == false)
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
            //player->shoot(world, textures[BULLET_TEXTURE_ID], textures[LIGHT_TRASSER_TEXTURE_ID], textures[STRAIGHT_TRASSER_TEXTURE_ID]);
            sendJson(ClientCommands::ROTATE, player->getRotation());
            sendJson(ClientCommands::SHOOT, true);
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
            SDL_Log("Id: %d, Type: %d, Coords: (%d %d), Grad: %d, Hp: %d\n",
                    (int)ent["objid"], (int)ent["tid"], (int)ent["x"], (int)ent["y"], (int)ent["rot"], (int)ent["hp"]);
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
        }
    }
}

void Game::sendJson(ClientCommands::ClientCommands command, int value) {
    nlohmann::json j;
    j["cmd"] = command;
    j["arg"] = value;
    net_client.send(j.dump());
    SDL_Log("SEND: %s", j.dump().c_str());
}
