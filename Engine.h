#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Engine {
private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;

public:
    Engine() : isRunning(false), window(nullptr), sdlRenderer(nullptr) {}

    bool init(const char* title, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL Error: " << SDL_GetError() << "\n";
            return false;
        }

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (!window) return false;

        sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!sdlRenderer) return false;

        isRunning = true;
        return true;
    }

    bool running() const { return isRunning; }
    SDL_Renderer* getRenderer() const { return sdlRenderer; }

    void handleEvents(class SandboxGame& sandbox, class TileMap& map, int camX, int camY) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            
            // Кліки мишкою (на телефонах це працює як звичайні тачі!)
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                
                int button = 1; // За замовчуванням лівий клік
                if (event.button.button == SDL_BUTTON_RIGHT) button = 3;

                // Передаємо в гру для обробки
                sandbox.handleInput(mouseX, mouseY, camX, camY, button, map);
            }
        }
    }

    void clearScreen() {
        SDL_SetRenderDrawColor(sdlRenderer, 20, 20, 20, 255);
        SDL_RenderClear(sdlRenderer);
    }

    void presentScreen() {
        SDL_RenderPresent(sdlRenderer);
    }

    void clean() {
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
