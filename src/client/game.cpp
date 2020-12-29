/*
Copyright 2020 LioKor Team (KoroLion, SergTyapkin, altanab, biotyree)
*/

#include <string>

#include "SDL.h"
#include "include/game.hpp"

Game::Game(std::string title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;
}

Game::~Game() {
    for (auto itr = game_objects.begin(); itr < game_objects.end(); itr++) {
        delete *itr;
    }
}

bool Game::start() {
    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow(
        this->title.c_str(),               // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        this->width,                       // width, in pixels
        this->height,                      // height, in pixels
        SDL_WINDOW_OPENGL);

    if (this->window == NULL) {
        return 1;
    }
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // this->game_objects.push_back(new MovingRect(10, 10, 50, 50, 0.5));
    this->game_objects.push_back(new SmallRect(5, 5));

    this->is_running = true;
    while (this->is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            this->handle_event(event);
        }

        this->render();

        SDL_Delay(17);  // ~ 60 FPS
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // white background
    SDL_RenderClear(renderer);

    for (auto itr = game_objects.begin(); itr < game_objects.end(); itr++) {
        (*itr)->update();
        (*itr)->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::handle_event(SDL_Event event) {
    bool quit_event = event.type == SDL_QUIT ||
        (event.type == SDL_WINDOWEVENT &&
        event.window.event == SDL_WINDOWEVENT_CLOSE);

    if (quit_event) {
        this->stop();
    }
}
