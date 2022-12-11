#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "MSound.h"
class Util
{

    static Util* clock;

    Uint32 minimum_fps_delta_time = (1000 / 6); // minimum 6 fps, if the computer is slower than this: slow down.
    Uint32 last_game_step = SDL_GetTicks(); // initial value
    uint32_t last_tick_time = 0;

    TTF_Font* font;

    int playerX;
    int playerY;




public:
    const int WIDTH = 962;
    const int HEIGHT = 962;
    bool DEBUG = false;

    SDL_Renderer* renderer;
    MSound sound;
    uint32_t deltaTime = 0;

    enum GAMESTATUS
    {
        PLAYING,
        GAMEOVER,
        MENU
    };
    GAMESTATUS gameStatus = MENU;

    void init();

    static Util* get();
    float distance(int x1, int y1, int x2, int y2);
    void showText(int x, int y, std::string text, SDL_Color fg = { 23, 187, 23 });
    void ticKClock();
    int randRange(int nMin, int nMax)
    {
        return nMin + (int)((double)rand() / (RAND_MAX + 1) * (nMax - nMin + 1));
    }


};


