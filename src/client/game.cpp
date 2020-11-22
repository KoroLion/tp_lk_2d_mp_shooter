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

#define WINDOW_X_INIT 300
#define WINDOW_Y_INIT 300
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

#define FPS 30

#define SEEK_ROTATION true
#define USE_MOUSE_FOR_ROTATE true
#define MOUSE_SENSIVITY 0.1


SDL_Texture* loadTexture(const char* imgName, SDL_Renderer* renderer, SDL_Surface* win_surf) {
    SDL_Surface* tmp_surf = SDL_LoadBMP(imgName);
    if (tmp_surf == NULL) {
        std::cout << "Can't load surface: " << SDL_GetError() << std::endl;
        return NULL;
    }
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

Game::Game(const char* _title, int _width, int _height): title(_title), width(_width), height(_height) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Can't init: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        title,               // window title
        WINDOW_X_INIT,           // initial x position
        WINDOW_Y_INIT,           // initial y position
        width,                       // width, in pixels
        height,                      // height, in pixels
        SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED
    );
    if (SEEK_ROTATION && USE_MOUSE_FOR_ROTATE) {
        //SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_ShowCursor(SDL_DISABLE);
    }

    if (window == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // аппаратный рендеринг + верт. синхронизация
    if (renderer == NULL) {
        std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Surface* win_surf = SDL_GetWindowSurface(window);
    for (const char* name: textureNames)
        textures.push_back(loadTexture(name, renderer, win_surf));

    world = new World(WINDOW_WIDTH, WINDOW_HEIGHT);

    Entity* targetForCamera = player = new Player(200,200, 40,100, 0, textures[BOX_TEXTURE_ID], 5);
    world->addEntity(0, targetForCamera);

    world->addEntity(1, new Obstacle(0,0, 0,0, 0, textures[BOX_TEXTURE_ID]));
    world->addEntity(2, new Obstacle(0,0, 0,0, 0, textures[BOX_TEXTURE_ID]));
    world->addEntity(3, new Obstacle(0,0, 0,0, 0, textures[BOX_TEXTURE_ID]));

    std::map<int, Entity*>* targetEntities = new std::map<int, Entity*>;
    targetEntities->insert(std::pair<const int, Entity*>(1, new Obstacle(50,120, 50,50, 30, NULL)));
    targetEntities->insert(std::pair<const int, Entity*>(2, new Obstacle(60,30, 60,60, -20, NULL)));
    targetEntities->insert(std::pair<const int, Entity*>(3, new Obstacle(300,250, 100,100, 0, NULL)));

    world->setTarget(targetEntities, 0);

    targetEntities = new std::map<int, Entity*>;
    targetEntities->insert(std::pair<const int, Entity*>(1, new Obstacle(50,120, 50,50, 30, NULL)));
    targetEntities->insert(std::pair<const int, Entity*>(2, new Obstacle(60,30, 60,60, 200, NULL)));
    targetEntities->insert(std::pair<const int, Entity*>(3, new Obstacle(300,250, 100,100, 0, NULL)));

    world->setTarget(targetEntities, 10000);

    camera = new Camera(width/2, height/2, WINDOW_WIDTH, WINDOW_HEIGHT, 0, world, targetForCamera, SEEK_ROTATION);
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::start() {
    FILE* f; fprintf(f = fopen("log.txt", "a+"), "%s\n", "Game started"); fclose(f);
    isRunning = true;
    time = 0;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            handleEvent(event);
        keyboardEvents();

        SDL_SetRenderDrawColor(renderer, SPLITRGBA(white_color));
        SDL_RenderClear(renderer);
        update();
        render();
        SDL_RenderPresent(renderer);

        time += 1000/FPS;
        SDL_Delay(1000/FPS);
    }
    return 0;
}

void Game::render() {
    camera->render(renderer);
}

void Game::update() {
    world->update(time);
    camera->update();
}

void Game::handleEvent(SDL_Event event) {
    bool quit_event = event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE ||
        (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE);

    if (quit_event)
        stop();
    switch (event.type) {
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
