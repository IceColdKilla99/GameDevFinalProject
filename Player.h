#pragma once
#include"GameObject.h" 
#include "DoublyLinkedList.h"
#include <iostream>
#include <string>
#include "MSound.h"

class Player : public GameObject
{
	enum STATE
	{
		IN_ROOM,
		IN_VENT
	};
	STATE state = IN_ROOM;

	int mouseX;
	int mouseY;

	int stayTime = 15;
	float countStayTime = 0;
	int numberOfDocCollected = 0;
public:

	Player(int x, int y, int speed) 
		:GameObject(x,y,speed,new SpriteSheet("assets/bird.png",4,1,4,48,48),PLAYER,1)
	{
		spriteSheet->setCurrent(2); // right
	}

	int getStayTime() {
		return stayTime;
	}
	void setStatyTime(int stayTime) {
		this->stayTime = stayTime;
	}

	void collect() {
		numberOfDocCollected++;
	}
	int getNumberOfDoc() {
		return numberOfDocCollected;
	}

	void update() {
		x += dirX * speed;
		y += dirY * speed;

		if (state == IN_ROOM) {
			countStayTime += Util::get()->deltaTime;
			if (countStayTime >= 1000) {
				countStayTime = 0;
				stayTime--;
				if (stayTime <= 3) {
					Util::get()->sound.playSound(MSound::SOUNDNAME::THREE_SECONDS_LEFT);
				}
				if (stayTime <= 0) { // 15 to 0
					Util::get()->sound.playSound(MSound::SOUNDNAME::SHOT);
					Util::get()->gameStatus = Util::GAMEOVER;
				}
			}
		}
		else {
			countStayTime = 0;
			stayTime = 15;
		}

		if (y <= 61 || x >= 898 || y >= 898) {
			state = IN_VENT;
		}
		else {
			state = IN_ROOM;
		}
		
	}

	void draw() {
		spriteSheet->follow(x, y);
		spriteSheet->draw();

		Util::get()->showText(507, 379, to_string(stayTime));
	}

	void onKeyDown(SDL_Keycode key) {
		if (key == SDLK_a) {
			dirX = -1;
			spriteSheet->setCurrent(2);
		}
		else if (key == SDLK_d) {
			dirX = 1;
			spriteSheet->setCurrent(3);
		}
		if (key == SDLK_w) {
			dirY = -1;
			spriteSheet->setCurrent(0);
		}
		else if (key == SDLK_s) {
			dirY = 1;
			spriteSheet->setCurrent(1);
		}
	}
	void onKeyUp(SDL_Keycode key) {
		if (key == SDLK_a && dirX == -1) {
			dirX = 0;
		}
		else if (key == SDLK_d && dirX == 1) {
			dirX = 0;
		}
		if (key == SDLK_w && dirY == -1) {
			dirY = 0;
		}
		else if (key == SDLK_s && dirY == 1) {
			dirY = 0;
		}
	}
};

