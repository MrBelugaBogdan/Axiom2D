#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

class MainMenu {
private:
    SDL_Rect buttonRect = { 350, 250, 200, 60 }; // Початкові координати кнопки
    bool isHovered = false;
    float pulseAngle = 0.0f; // Для плавної анімації коливання

public:
    void update(int mouseX, int mouseY) {
        // Перевіряємо, чи наведена мишка на кнопку
        isHovered = (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
                     mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h);

        if (isHovered) {
            pulseAngle += 0.1f; // Швидкість пульсації
        } else {
            pulseAngle = 0.0f;
        }
    }

    void render(SDL_Renderer* r) {
        // Рендеримо темний фон меню
        SDL_SetRenderDrawColor(r, 15, 15, 25, 255);
        SDL_RenderClear(r);

        // Розраховуємо ефект "шевеління" для кнопки
        int drawW = buttonRect.w;
        int drawH = buttonRect.h;
        int drawX = buttonRect.x;
        int drawY = buttonRect.y;

        if (isHovered) {
            // Кнопка плавно збільшується на 5-10 пікселів за синусоїдою
            int scale = (int)(sin(pulseAngle) * 5.0f);
            drawW += scale * 2;
            drawH += scale;
            drawX -= scale;
            drawY -= scale / 2;
        }

        // Малюємо тінь кнопки
        SDL_SetRenderDrawColor(r, 0, 0, 0, 150);
        SDL_Rect shadow = { drawX + 4, drawY + 4, drawW, drawH };
        SDL_RenderFillRect(r, &shadow);

        // Малюємо саму кнопку (наприклад, помаранчеву)
        if (isHovered) {
            SDL_SetRenderDrawColor(r, 255, 140, 0, 255); // Яскрава при наведенні
        } else {
            SDL_SetRenderDrawColor(r, 200, 80, 0, 255);  // Звичайна
        }
        SDL_Rect button = { drawX, drawY, drawW, drawH };
        SDL_RenderFillRect(r, &button);

        // Рамка кнопки
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderDrawRect(r, &button);
    }

    bool checkClick(int mouseX, int mouseY) {
        return (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
                mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h);
    }
};
