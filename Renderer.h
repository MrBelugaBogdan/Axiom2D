#pragma once
#include <SDL2/SDL.h>
#include "TileMap.h"

class Renderer {
private:
    int tileWidth = 64;
    int tileHeight = 32;

public:
    // Перетворення координат сітки в ізометричні координати екрана
    void mapToScreen(int col, int row, int& screenX, int& screenY) {
        screenX = (col - row) * (tileWidth / 2);
        screenY = (col + row) * (tileHeight / 2);
    }

    void render(SDL_Renderer* sdlRenderer, TileMap& map, int camX, int camY) {
        for (int x = 0; x < TileMap::WIDTH; ++x) {
            for (int y = 0; y < TileMap::HEIGHT; ++y) {
                int screenX, screenY;
                mapToScreen(x, y, screenX, screenY);

                // Додаємо зсув камери
                int drawX = screenX + camX;
                int drawY = screenY + camY;

                // Вибираємо колір залежно від ID блоку
                Tile tile = map.grid[x][y];
                if (tile.id == 0) {
                    SDL_SetRenderDrawColor(sdlRenderer, 30, 144, 255, 255); // Синя вода
                } else if (tile.id == 1) {
                    SDL_SetRenderDrawColor(sdlRenderer, 34, 139, 34, 255);  // Зелена трава
                } else if (tile.id == 2) {
                    SDL_SetRenderDrawColor(sdlRenderer, 128, 128, 128, 255); // Сіра дорога
                }

                drawIsoFilledTile(sdlRenderer, drawX, drawY);
            }
        }
    }

private:
    // Малюємо зафарбований ізометричний ромб
    void drawIsoFilledTile(SDL_Renderer* r, int x, int y) {
        // Малюємо кілька ліній по вертикалі, щоб заповнити ромб кольором
        for (int i = 0; i <= tileHeight / 2; ++i) {
            int span = i * 2;
            SDL_RenderDrawLine(r, x + tileWidth / 2 - span, y + i, x + tileWidth / 2 + span, y + i);
        }
        for (int i = 0; i <= tileHeight / 2; ++i) {
            int span = (tileHeight / 2 - i) * 2;
            SDL_RenderDrawLine(r, x + tileWidth / 2 - span, y + tileHeight / 2 + i, x + tileWidth / 2 + span, y + tileHeight / 2 + i);
        }

        // Малюємо чорну рамку навколо блоку для чіткості сітки
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderDrawLine(r, x, y + tileHeight / 2, x + tileWidth / 2, y);
        SDL_RenderDrawLine(r, x + tileWidth / 2, y, x + tileWidth, y + tileHeight / 2);
        SDL_RenderDrawLine(r, x + tileWidth, y + tileHeight / 2, x + tileWidth / 2, y + tileHeight);
        SDL_RenderDrawLine(r, x + tileWidth / 2, y + tileHeight, x, y + tileHeight / 2);
    }
};
