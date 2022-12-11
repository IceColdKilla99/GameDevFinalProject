#pragma once
#include <vector>
#include <iostream>
#include "Map.h"
#include "Table.h"
#include "Guard.h"
#include "Wall.h"
#include "GreenDoor.h"
#include "DoublyLinkedList.h"

using namespace std;

class Game {

	Map map;
	GameObject* player;
	dLinkedList* objects;

public:
	Game() {
		Util::get()->sound.playMenuMusic();
	}

	void startGame() {
		objects = new dLinkedList;
		player = new Player(100, 200, 4);
		GameObject* table1 = new Table(352, 342, 0,"assets/fake3.png", "assets/real3.png",1);
		GameObject* table2 = new Table(767, 75, 0, "assets/real4.png", "assets/fake4.png",0);
		GameObject* guard1 = new Guard(164, 701, 1, 4000, player,200);
		GameObject* guard2 = new Guard(569, 578, 1, 3000, player,100);

		GameObject* wall1 = new Wall(485, 69, 72, 694);
		GameObject* wall2 = new Wall(168, 59, 733, 10);
		GameObject* wall3 = new Wall(0, -5, 962, 10);
		GameObject* wall4 = new Wall(958, 0, 6, 962);
		GameObject* wall5 = new Wall(895, 64, 10, 327);
		GameObject* wall6 = new Wall(0, 958, 962, 10);
		GameObject* wall7 = new Wall(258, 894, 640, 10);
		GameObject* wall8 = new Wall(895, 455, 10, 452);
		GameObject* wall9 = new Wall(0, 0, 6, 962);

		GameObject* exit = new GreenDoor(-5, 349, player);


		objects->headInsert(table1);
		objects->headInsert(table2);


		objects->headInsert(player);

		objects->headInsert(guard1);
		objects->headInsert(guard2);

		objects->headInsert(wall1);
		objects->headInsert(wall2);
		objects->headInsert(wall3);
		objects->headInsert(wall4);
		objects->headInsert(wall5);
		objects->headInsert(wall6);
		objects->headInsert(wall7);
		objects->headInsert(wall8);
		objects->headInsert(wall9);

		objects->headInsert(exit);
		Util::get()->sound.playGameMusic();
	}

	void update() {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			return;
		}

		for (node* n = objects->head; n != NULL; n = n->next) {
			GameObject* obj = n->data;
			obj->update();
			if (obj->isDead()) {
				objects->deleteNode(n);
				break;
			}
		}

		checkCollide();
	}

	void onKeyDown(SDL_Keycode key) {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			if (key == SDLK_SPACE) {
				Util::get()->gameStatus = Util::PLAYING;
				startGame();
			}
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			if (key == SDLK_SPACE) {
				Util::get()->gameStatus = Util::PLAYING;
				startGame();
			}
			return;
		}

		((Player*)player)->onKeyDown(key);
	}
	void onKeyUp(SDL_Keycode key) {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			return;
		}
		((Player*)player)->onKeyUp(key);
	}
	void onMouseDown(int x, int y) {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			return;
		}
		for (node* n = objects->head; n != NULL; n = n->next) {
			GameObject* obj = n->data;
			obj->onMouseDown(x, y);
		}
	}

	void draw() {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			Util::get()->showText(350, 200, "Game Over!");
			Util::get()->showText(350, 500, "Pegion Impossible!");
			Util::get()->showText(350, 600, "Press 'Space' to retry!");
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			Util::get()->showText(350, 200, "Pegion Impossible!");
			Util::get()->showText(350, 300, "Press 'Space' to start the game");
			return;
		}


		// in game
		map.draw();
		for (node* n = objects->head; n != NULL; n = n->next) {
			GameObject* obj = n->data;
			obj->draw();
		}
	}

	void checkCollide() { // check collision for all objects

		for (node* n = objects->head; n != NULL; n = n->next) {
			GameObject* obj = n->data;

			for (node* m = objects->head; m != NULL; m = m->next) {
				GameObject* otherObj = m->data;
				if (obj == otherObj) {
					continue;
				}
				if (obj->checkCollide(otherObj)) { // check collide 
					obj->onCollide(otherObj); // if collide call onCollide
				}
			}
		}
	}
};