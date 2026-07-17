#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

enum EngineState { STATE_MENU, STATE_GAME };

class Engine {
private:
    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    EngineState state = STATE_MENU;

public:
    SDL_Texture* texGrass = nullptr;
    SDL_Texture* texRoad = nullptr;
    SDL_Texture* texWater = nullptr;

    bool init(const char* title, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
        
        // Ініціалізація завантажувача картинок PNG
        IMG_Init(IMG_INIT_PNG);

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        isRunning = true;
        loadDefaultTextures();
        return true;
    }

    void loadDefaultTextures() {
        // Створюємо тимчасові дефолтні текстури (якщо немає файлів)
        // В реальному проєкті тут буде IMG_LoadTexture(sdlRenderer, "assets/grass.png");
        texGrass = createColorTexture(34, 139, 34);   // Зелена трава
        texRoad = createColorTexture(128, 128, 128);  // Сіра дорога
        texWater = createColorTexture(30, 144, 255);  // Синя вода
    }

    SDL_Texture* createColorTexture(Uint8 r, Uint8 g, Uint8 b) {
        SDL_Surface* surf = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0);
        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, r, g, b));
        SDL_Texture* tex = SDL_CreateTextureFromSurface(sdlRenderer, surf);
        SDL_FreeSurface(surf);
        return tex;
    }

    EngineState getState() const { return state; }
    void setState(EngineState newState) { state = newState; }
    bool running() const { return isRunning; }
    SDL_Renderer* getRenderer() const { return sdlRenderer; }
    void stop() { isRunning = false; }

    void clean() {
        SDL_DestroyTexture(texGrass);
        SDL_DestroyTexture(texRoad);
        SDL_DestroyTexture(texWater);
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }
};
