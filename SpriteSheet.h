#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include"Util.h"

class SpriteSheet
{
	int rows;
	int cols;
	int count;

	int sizeX;
	int sizeY;

	SDL_Texture* texture;
	SDL_Rect dstrect;
	SDL_Rect srcrect;

	int x; int y;

	int start;
	int end;
	int current;
	int delay;
	int playTime = 0;

	bool finishLoop = false;
	bool loop;
public:

	SpriteSheet(const char* path, int rows, int cols, int count, int sizeX, int sizeY,bool loop = false);
	void draw(bool d = false);

	void setLoop(int start, int end, int delay);
	void playAnimation();
	void follow(int x, int y);
	void setCurrent(int i) {
		current = i;
	}

	SDL_Texture* getTexture();

	SDL_Rect getRect();
	SDL_Rect getSrcRect() {
		return srcrect;
	}
	int getCurrent();
	bool getFinishLoop();

};

