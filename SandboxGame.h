#pragma once
#include "TileMap.h"
#include <iostream>

class SandboxGame {
private:
    int tileWidth = 64;
    int tileHeight = 32;

public:
    // Перетворюємо клік мишки/тач на екрані назад у координати нашої сітки
    void handleInput(int screenX, int screenY, int camX, int camY, int buttonType, TileMap& map) {
        // Прибираємо зсув камери
        float relativeX = (float)(screenX - camX);
        float relativeY = (float)(screenY - camY);

        // Складна ізометрична математика зворотного перетворення
        int col = (int)((relativeX / (tileWidth / 2.0f) + relativeY / (tileHeight / 2.0f)) / 2.0f);
        int row = (int)((relativeY / (tileHeight / 2.0f) - relativeX / (tileWidth / 2.0f)) / 2.0f);

        // Перевіряємо, чи ми не промахнулися повз карту
        if (col >= 0 && col < TileMap::WIDTH && row >= 0 && row < TileMap::HEIGHT) {
            if (buttonType == 1) { // Лівий клік миші або тач
                map.setTile(col, row, 2); // Будуємо СІРУ ДОРОГУ!
                std::cout << "[Axiom2D] Побудовано дорогу на плиточці: (" << col << ", " << row << ")\n";
            } 
            else if (buttonType == 3) { // Правий клік
                map.setTile(col, row, 0); // Викопуємо ВАТЕРБЛОК (вода)
                std::cout << "[Axiom2D] Викопано блок води на плиточці: (" << col << ", " << row << ")\n";
            }
        }
    }
};
