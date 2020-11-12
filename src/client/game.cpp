/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/
#include <iostream>

#include <vector>

#include "SDL.h"
#include "include/Game.hpp"
#include "include/World.hpp"
#include "include/Colors.hpp"

#define FPS 60

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
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        width,                       // width, in pixels
        height,                      // height, in pixels
        SDL_WINDOW_OPENGL
    );

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

    world = new World(800, 600);
    world->addEntity(new Obstacle(50,120, 50,50, 30, textures[BOX_TEXTURE_ID]));
    world->addEntity(new Obstacle(60,30, 60,60, -20, textures[BOX_TEXTURE_ID]));
    world->addEntity(new Obstacle(30,200, 100,100, 45, textures[BOX_TEXTURE_ID]));

}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::start() {
    FILE* f; fprintf(f = fopen("log.txt", "a+"), "%s\n", "Game started"); fclose(f);
    isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handle_event(event);
        }

        SDL_SetRenderDrawColor(renderer, SPLITRGBA(white_color));
        SDL_RenderClear(renderer);
        update();
        render();
        SDL_RenderPresent(renderer);

        SDL_Delay(1000/FPS);
    }

    return 0;
}

void Game::render() {
    world->render(renderer);
}

void Game::update() {
    world->update();
}

void Game::handle_event(SDL_Event event) {
    bool quit_event = event.type == SDL_QUIT ||
        (event.type == SDL_WINDOWEVENT &&
        event.window.event == SDL_WINDOWEVENT_CLOSE);

    if (quit_event) {
        stop();
    }
}
