#include <SDL.h>
#include <SDL_image.h>
#include<iostream>
#include "Util.h"
#include "SpriteSheet.h"
#include "Player.h"
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "DoublyLinkedList.h"
#include "MSound.h"
#include "Game.h"

using namespace std;


/////

int main(int argc, char** argv)
{
	srand(time(nullptr));



	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Event event;

	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);



	//Initialize the truetype font API.
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return -1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
	}

	
	//Load Sound Effect
	Util::get()->init();

	SDL_Window* window = SDL_CreateWindow("Shooter game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Util::get()->WIDTH, Util::get()->HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	Util::get()->renderer = renderer;
	bool quit = false;

	Game game;

	while (!quit)
	{

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		Util::get()->ticKClock();


		SDL_Event event;
		int numKeys;
		const Uint8* keys = SDL_GetKeyboardState(&numKeys);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				game.onKeyDown(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				game.onKeyUp(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				printf("click: %d - %d\n", event.button.x, event.button.y);
				game.onMouseDown(event.button.x, event.button.y);
			}

		}

		game.update();
		game.draw();

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}



