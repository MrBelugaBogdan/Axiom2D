#include "Engine.h"
#include "TileMap.h"
#include "Renderer.h"
#include "SandboxGame.h"

int main(int argc, char* argv[]) {
    Engine core;
    
    if (!core.init("Axiom2D Sandbox (Minetest-Style)", 900, 650)) {
        return -1;
    }

    TileMap map;              // Створюємо порожню зелену карту світу
    Renderer renderer;        // Наш ізометричний рендерер
    SandboxGame sandbox;      // Наш дефолтний ігровий режим

    // Початкове позиціонування камери, щоб бачити красиву карту по центру
    int cameraX = 450;
    int cameraY = 100;

    std::cout << "=========================================\n";
    std::cout << "🎮 Axiom2D ENGINE ЗАПУЩЕНО 🎮\n";
    std::cout << "ЛКМ (Тач) -> Побудувати дорогу\n";
    std::cout << "ПКМ -> Створити водойму (воду)\n";
    std::cout << "=========================================\n";

    while (core.running()) {
        core.handleEvents(sandbox, map, cameraX, cameraY);
        core.clearScreen();

        // Рендеримо нашу карту
        renderer.render(core.getRenderer(), map, cameraX, cameraY);

        core.presentScreen();
    }

    core.clean();
    return 0;
}
