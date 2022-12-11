#pragma once
#include"GameObject.h" 
#include "DoublyLinkedList.h"
#include <iostream>
#include <string>
#include "MSound.h"

class Wall : public GameObject
{
	GameObject* player = nullptr;
public:

	Wall(int x, int y, int w,int h)
		:GameObject(x, y, 0, new SpriteSheet("null.png", 1, 1, 1, w, h), WALL, 1)
	{
		spriteSheet->follow(x, y);
	}

	void update() {

	}

	void onCollide(GameObject* other) {
		if (other->getType() == PLAYER) {
			player = other;
			SDL_Rect playerRect = other->getRect();
			SDL_Rect wallRect = getRect();

			// stop player
			if (playerRect.y + playerRect.h > wallRect.y && wallRect.y > playerRect.y)
			{
				float diff = playerRect.y + playerRect.h - wallRect.y;
				//player->setDirXy(player->getDirX(), 0);
				player->setXY(player->getX(), playerRect.y - diff );
			}
			else if (playerRect.y + playerRect.h < wallRect.y + wallRect.h && playerRect.x + playerRect.w > wallRect.x && playerRect.x < wallRect.x) {
				float diff = playerRect.x + playerRect.w - wallRect.x;
				player->setXY(playerRect.x - diff, playerRect.y);
				//player->setDirXy(player->getDirX(), 0);
			}
			else if (playerRect.y + playerRect.h < wallRect.y + wallRect.h && playerRect.x < wallRect.x + wallRect.w && playerRect.x + playerRect.w > wallRect.x) {
				float diff = wallRect.x + wallRect.w - playerRect.x;
				player->setXY(playerRect.x + diff, playerRect.y);
				//player->setDirXy(0, 0);
			}
			else if (wallRect.y + wallRect.h > playerRect.y && playerRect.y > wallRect.y)
			{
				float diff = wallRect.y + wallRect.h - playerRect.y;
				//player->setDirXy(player->getDirX(), 0);
				player->setXY(player->getX(), playerRect.y + diff );
			}
		}
	}

	void draw() {
		if (Util::get()->DEBUG) {
			drawRectangle(getRect());
		}
	}
};

