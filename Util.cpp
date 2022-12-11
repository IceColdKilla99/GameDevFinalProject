#include "Util.h"

Util* Util::clock = nullptr;
void Util::ticKClock() {
   
    Uint32 now = SDL_GetTicks();

    // Check so we don't render for no reason, avoid having a 0 delta time
    if (last_game_step < now) {

        Uint32 delta_time = now - last_game_step;

        if (delta_time > minimum_fps_delta_time) {
            delta_time = minimum_fps_delta_time; // slow down if the computer is too slow
        }
        deltaTime = delta_time;

        last_game_step = now;
    }
}

float Util::distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void Util::showText(int x, int y, std::string text, SDL_Color fg ) {

    //SDL_Color fg = { 23, 187, 23 };
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    surface = TTF_RenderText_Solid(font, text.c_str(), fg);
    texture = SDL_CreateTextureFromSurface(Util::get()->renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;

    desRect.x = x;
    desRect.y = y;

    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
    SDL_RenderCopy(Util::get()->renderer, texture, &srcRest, &desRect);
    SDL_DestroyTexture(texture);
}


void Util::init()
{
    font = TTF_OpenFont("assets/font.ttf", 24);
}

Util* Util::get()
{
    if (clock == nullptr) {
        clock = new Util();
    }
    return clock;
}