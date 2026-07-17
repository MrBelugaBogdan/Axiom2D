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
            std::cerr << "SDL не зміг запуститися! Error: " << SDL_GetError() << "\n";
            return false;
        }

        // На мобільному телефоні SDL автоматично розгорне вікно на весь екран
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (!window) return false;

        // Створюємо швидкий апаратний рендерер з підтримкою вертикальної синхронізації (VSync)
        sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!sdlRenderer) return false;

        isRunning = true;
        return true;
    }

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            // Обробка тачу на екрані смартфона
            if (event.type == SDL_FINGERDOWN) {
                float touchX = event.tfinger.x; // Координати від 0.0 до 1.0
                float touchY = event.tfinger.y;
                std::cout << "Тач на екрані смартфона: " << touchX << ", " << touchY << "\n";
            }
        }
    }

    void clearScreen() {
        SDL_SetRenderDrawColor(sdlRenderer, 20, 20, 20, 255); // Темний фон підкладки
        SDL_RenderClear(sdlRenderer);
    }

    void presentScreen() {
        SDL_RenderPresent(sdlRenderer);
    }

    bool running() const { return isRunning; }
    SDL_Renderer* getRenderer() const { return sdlRenderer; }

    void clean() {
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        std::cout << "Двигун успішно зупинено.\n";
    }
};
