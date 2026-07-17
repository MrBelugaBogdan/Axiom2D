#pragma once
#include <SDL2/SDL.h>
#include "TileMap.h"
#include "Engine.h"

class Renderer {
private:
    int tileWidth = 64;
    int tileHeight = 32;

public:
    void render(SDL_Renderer* sdlRenderer, TileMap& map, Engine& core, int camX, int camY) {
        for (int x = 0; x < TileMap::WIDTH; ++x) {
            for (int y = 0; y < TileMap::HEIGHT; ++y) {
                int screenX = (x - y) * (tileWidth / 2) + camX;
                int screenY = (x + y) * (tileHeight / 2) + camY;

                Tile tile = map.grid[x][y];
                SDL_Texture* currentTex = nullptr;

                // Обираємо правильну текстуру двигуна
                if (tile.id == 0) currentTex = core.texWater;
                else if (tile.id == 1) currentTex = core.texGrass;
                else if (tile.id == 2) currentTex = core.texRoad;

                if (currentTex) {
                    // Малюємо текстуру, вписану в ромбоподібні межі
                    SDL_Rect destRect = { screenX, screenY, tileWidth, tileHeight };
                    SDL_RenderCopy(sdlRenderer, currentTex, NULL, &destRect);
                }

                // Малюємо сітку поверх для краси
                SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 50);
                SDL_RenderDrawLine(sdlRenderer, screenX, screenY + tileHeight / 2, screenX + tileWidth / 2, screenY);
                SDL_RenderDrawLine(sdlRenderer, screenX + tileWidth / 2, screenY, screenX + tileWidth, screenY + tileHeight / 2);
                SDL_RenderDrawLine(sdlRenderer, screenX + tileWidth, screenY + tileHeight / 2, screenX + tileWidth / 2, screenY + tileHeight);
                SDL_RenderDrawLine(sdlRenderer, screenX + tileWidth / 2, screenY + tileHeight, screenX, screenY + tileHeight / 2);
            }
        }
    }
};
