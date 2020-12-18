/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab)
*/
#include <iostream>
#include <math.h>
#include <vector>
#include <windows.h>

#include "SDL.h"
#include "include/Game.hpp"
#include "include/World.hpp"
#include "include/Camera.hpp"
#include "include/Colors.hpp"
#include "include/Entities.hpp"

#define WINDOW_X_INIT 300
#define WINDOW_Y_INIT 300
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

#define FPS 60

#define SEEK_ROTATION false
#define USE_MOUSE_FOR_ROTATE true
#define MOUSE_SENSIVITY 0.1

#define BOX_TEXTURE_ID              0
#define BG_TEXTURE_ID               1
#define BG_VIGNETTE_TEXTURE_ID      2
#define PLAYER_TEXTURE_ID           3
#define BULLET_TEXTURE_ID           4
#define LIGHT_TRASSER_TEXTURE_ID    5
#define STRAIGHT_TRASSER_TEXTURE_ID 6

SDL_Texture* loadTexture(const char* imgName, SDL_Renderer* renderer, SDL_Surface* win_surf, Uint8 r = -1, Uint8 g = -1, Uint8 b = -1) {
    SDL_Surface* tmp_surf = SDL_LoadBMP(imgName);
    if (tmp_surf == NULL) {
        std::cout << "Can't load surface: " << SDL_GetError() << std::endl;
        return NULL;
    }
    if (r != -1)
        SDL_SetColorKey(tmp_surf, SDL_TRUE, SDL_MapRGB(tmp_surf->format, r,g,b));
    /*
    tmp_surf = SDL_ConvertSurface(tmp_surf, win_surf->format, 0);
    if (tmp_surf == NULL) {
        std::cout << "Can't convert to new format: " << SDL_GetError() << std::endl;
        return NULL;
    }
    */
    SDL_Texture* tmp_texture = SDL_CreateTextureFromSurface(renderer, tmp_surf);
    if (tmp_texture == NULL) {
        std::cout << "Can't conver surf to texture: " << SDL_GetError() << std::endl;
        return NULL;
    }
    return tmp_texture;
}

Game::Game(const char* _title, int _width, int _height): title(_title), width(_width), height(_height),
        net_client("localhost", "23000", std::bind(
            netEventCallback,
            this,
            std::placeholders::_1,
            std::placeholders::_2
        )) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Can't init: " << SDL_GetError() << std::endl;
        return;
    }

    if ((window = SDL_CreateWindow(title, WINDOW_X_INIT, WINDOW_Y_INIT, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED)) == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        return;
    }

    if (SEEK_ROTATION && USE_MOUSE_FOR_ROTATE) {
        //SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_ShowCursor(SDL_DISABLE);
    }

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
        std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
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

    world = new World(WINDOW_WIDTH, WINDOW_HEIGHT, textures[BG_TEXTURE_ID], textures[BG_VIGNETTE_TEXTURE_ID]);

    player = new Player(200,200,2, 40,40, 0, textures[PLAYER_TEXTURE_ID], 5);
    world->addEntity(0, player);

    world->addEntity(1, new Obstacle(0,0,0, 0,0, 0, textures[BOX_TEXTURE_ID]));
    world->addEntity(2, new Obstacle(0,0,0, 0,0, 0, textures[BOX_TEXTURE_ID]));
    world->addEntity(3, new Obstacle(0,0,0, 0,0, 0, textures[BOX_TEXTURE_ID]));

    std::map<int, Entity*>* targetEntities = new std::map<int, Entity*>;
    targetEntities->insert(std::pair<const int, Entity*>(1, new Obstacle(50,120,1, 50,50, 30, NULL)));
    targetEntities->insert(std::pair<const int, Entity*>(2, new Obstacle(60,30,1, 60,60, -20, NULL)));
    targetEntities->insert(std::pair<const int, Entity*>(3, new Obstacle(300,250,2, 100,200, 0, NULL)));

    world->setTarget(targetEntities, 0);

    targetEntities = new std::map<int, Entity*>;
    targetEntities->insert(std::pair<const int, Entity*>(1, new Obstacle(50,120,1, 50,50, 30, NULL)));
    targetEntities->insert(std::pair<const int, Entity*>(2, new Obstacle(60,30,1, 60,60, 200, NULL)));
    targetEntities->insert(std::pair<const int, Entity*>(3, new Obstacle(300,250,2, 100,200, 0, NULL)));

    world->setTarget(targetEntities, 10000);

    camera = new Camera(width/2, height/2, 10, 60, WINDOW_WIDTH, WINDOW_HEIGHT, 0, world, player, SEEK_ROTATION);
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
    } catch (std::exception e) {
        std::cout << "WARNING: Failed to connect!" << std::endl;
        return 1;
    }

    return 0;
}

void Game::netEventCallback(NetServerEventType evType, std::string data) {
    if (evType == CONNECTED) {
        std::cout << "INFO: Connected!" << std::endl;
    } else if (evType == MESSAGE) {
        std::cout << "RECEIVED: " << data << std::endl;
    } else if (evType == DISCONNECTED) {
        std::cout << "INFO: Disconnected!" << std::endl;
    }
}

bool Game::start() {
    DWORD tid = 0;
    HANDLE ht = CreateThread(NULL, 0, networkThreadLauncher, this, 0, &tid);
    if (ht == NULL) {
        std::cout << "ERROR: Unable to start thread!" << std::endl;
        throw std::exception();
    }

    FILE* f; fprintf(f = fopen("log.txt", "a+"), "%s\n", "Game started"); fclose(f);
    isRunning = true;
    time = 0;
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
    world->update(time);
    camera->update();
}

void Game::handleEvent(SDL_Event* event) {
    bool quit_event = event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE ||
        (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE);

    if (quit_event)
        stop();
    switch (event->type) {
    /*case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_w:
            player->moveRelative(0);
            break;
        case SDLK_a:
            if (USE_MOUSE_FOR_ROTATE)
                player->moveRelative(-90);
            else
                player->rotateRelative(-10);
            break;
        case SDLK_s:
            player->moveRelative(180);
            break;
        case SDLK_d:
            if (USE_MOUSE_FOR_ROTATE)
                player->moveRelative(90);
            else
                player->rotateRelative(10);
            break;
        }
        break;*/
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
        } else {
            SDL_GetMouseState(&mouseX, &mouseY);
            player->setRotation(getAngle(width/2, height/2, mouseX, mouseY));
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        switch (event->button.button) {
        case SDL_BUTTON_LEFT:
            player->shoot(world, textures[BULLET_TEXTURE_ID], textures[LIGHT_TRASSER_TEXTURE_ID], textures[STRAIGHT_TRASSER_TEXTURE_ID]);
            break;
        }
        break;
    }
}

void Game::keyboardEvents() {
    const Uint8 *keys = SDL_GetKeyboardState(0);
    if (SEEK_ROTATION || !USE_MOUSE_FOR_ROTATE) {
        if (keys[SDL_SCANCODE_W])
            player->moveRelative(0);
        if (keys[SDL_SCANCODE_A])
            if (USE_MOUSE_FOR_ROTATE)
                player->moveRelative(-90);
            else
                player->rotateRelative(-10);
        if (keys[SDL_SCANCODE_S])
            player->moveRelative(180);
        if (keys[SDL_SCANCODE_D])
            if (USE_MOUSE_FOR_ROTATE)
                player->moveRelative(90);
            else
                player->rotateRelative(10);
    } else {
        if (keys[SDL_SCANCODE_W])
            player->moveAbsolute(0, -player->getSpeed());
        if (keys[SDL_SCANCODE_A])
            player->moveAbsolute(-player->getSpeed(), 0);
        if (keys[SDL_SCANCODE_S])
            player->moveAbsolute(0, player->getSpeed());
        if (keys[SDL_SCANCODE_D])
            player->moveAbsolute(player->getSpeed(), 0);
    }
}
