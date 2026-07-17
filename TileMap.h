#pragma once
#include <vector>

struct Tile {
    int id = 1;             // 0: Вода, 1: Трава, 2: Дорога
    bool isWalkable = true; // Чи можна ходити/їхати
};

class TileMap {
public:
    static const int WIDTH = 15;
    static const int HEIGHT = 15;
    Tile grid[WIDTH][HEIGHT];

    TileMap() {
        // Заповнюємо карту дефолтною зеленою травою (ID = 1)
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                grid[x][y].id = 1;
                grid[x][y].isWalkable = true;
            }
        }
    }

    void setTile(int x, int y, int typeID) {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            grid[x][y].id = typeID;
            grid[x][y].isWalkable = (typeID != 0); // По воді ходити не можна
        }
    }
};
