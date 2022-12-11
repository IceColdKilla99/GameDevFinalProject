#include "SpriteSheet.h"
#include <iostream>

SpriteSheet::SpriteSheet(const char* path,int rows,int cols,int count,int sizeX,int sizeY,bool loop)
{
	SDL_Surface* image = IMG_Load(path);
	texture = SDL_CreateTextureFromSurface(Util::get()->renderer, image);
	this->rows = rows;
	this->cols = cols;
	this->count = count;

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->loop = loop;
}

void SpriteSheet::draw(bool d)
{
	int spriteRow = current / cols;
	int spriteCol = current % cols;

	srcrect = { sizeX * spriteCol, sizeY * spriteRow, sizeX, sizeY };
	dstrect = { x, y, sizeX, sizeY };

	if (!d) {
		SDL_RenderCopy(Util::get()->renderer, texture, &srcrect, &dstrect);
	}

	/*SDL_SetRenderDrawColor(Util::get()->renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(Util::get()->renderer, &dstrect);*/
}

void SpriteSheet::setLoop(int start, int end, int delay)
{

	//std::cout << start << "=" << end << "\n";
	if (this->start == start && this->end == end) {
		return;
	}
	this->start = start;
	this->end = end;
	this->current = start;
	this->delay = delay;
}

void SpriteSheet::playAnimation()
{
	if (!loop) {
		return;
	}

	playTime += Util::get()->deltaTime;
	if (playTime >= delay) {
		playTime = 0;

		current++;
		if (current >= end) {
			if (current == 15) {
				finishLoop = true;
			}
			current = start;
		}
	}
}

void SpriteSheet::follow(int x, int y)
{
	this->x = x;
	this->y = y;
	dstrect = { x, y, sizeX, sizeY };
}

SDL_Texture* SpriteSheet::getTexture()
{
	return texture;
}

SDL_Rect SpriteSheet::getRect()
{
	return dstrect;
}

int SpriteSheet::getCurrent()
{
	return current;
}

bool SpriteSheet::getFinishLoop()
{
	return finishLoop;
}
