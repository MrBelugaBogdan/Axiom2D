#include "Engine.h"
#include "TileMap.h"
#include "Renderer.h"
#include "SandboxGame.h"
#include "MainMenu.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// Глобальні об'єкти для роботи циклу в браузері
Engine core;
TileMap map;
Renderer tileRenderer;
SandboxGame sandbox;
MainMenu menu;
int camX = 400;
int camY = 100;

void mainLoop() {
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    // 1. Обробка подій
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            core.stop();
        }

        if (core.getState() == STATE_MENU) {
            menu.update(mouseX, mouseY);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (menu.checkClick(mouseX, mouseY)) {
                    core.setState(STATE_GAME); // Перехід у гру!
                }
            }
        } 
        else if (core.getState() == STATE_GAME) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int button = (event.button.button == SDL_BUTTON_RIGHT) ? 3 : 1;
                sandbox.handleInput(mouseX, mouseY, camX, camY, button, map);
            }
        }
    }

    // 2. Рендеринг кадру
    core.clearScreen();

    if (core.getState() == STATE_MENU) {
        menu.update(mouseX, mouseY);
        menu.render(core.getRenderer());
    } 
    else if (core.getState() == STATE_GAME) {
        tileRenderer.render(core.getRenderer(), map, core, camX, camY);
    }

    core.presentScreen();
}

int main(int argc, char* argv[]) {
    if (!core.init("Axiom2D Web Engine", 900, 600)) {
        return -1;
    }

#ifdef __EMSCRIPTEN__
    // Якщо запущено в браузері — передаємо цикл під керування браузера (60 FPS)
    emscripten_set_main_loop(mainLoop, 0, 1);
#else
    // Звичайний запуск на ПК
    while (core.running()) {
        mainLoop();
        SDL_Delay(16); // ~60 FPS
    }
    core.clean();
#endif

    return 0;
}
