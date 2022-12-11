#pragma once
#include "MSound.h"
#include "SpriteSheet.h"
class GameObject
{
public:

	enum TYPE
	{
		PLAYER,
		ENEMY,
		TABLE,
		WALL
	};

protected:
	SpriteSheet* spriteSheet;
	float x, y;
	int speed;
	bool isAlive = true;
	int life;
	int size = 64;
	TYPE type;

	int dirX = 0;
	int dirY = 0;

public:

	GameObject(int x, int y, int speed, SpriteSheet* sheet,TYPE type,int life = 1);

	virtual void update() = 0;
	virtual void draw();


	int getX();
	int getY();

	bool moveTo(int toX, int toY);
	float point_distance(int x1, int y1, int x2, int y2);
	bool checkCollide(GameObject * obj);
	static bool checkClickCollide(SDL_Rect a,int x, int y);
	virtual void onCollide(GameObject* obj){}
	virtual void onMouseDown(int x,int y){}

	void setAlive(bool alive) {
		this->isAlive = alive;
	}

	virtual SDL_Rect getRect() {
		return spriteSheet->getRect();
	}

	int getLife() { return life; }
	void setLife(int l) {
		life = l;
		if (life <= 0) {
			isAlive = false;
		}
	}

	bool isDead();

	TYPE getType() {
		return type;
	}
	void setY(int y) {
		this->y = y;
	}

	void drawRectangle(SDL_Rect r) {
		SDL_SetRenderDrawColor(Util::get()->renderer, 0, 233, 233, 255);
		//SDL_RenderFillRect(Util::get()->renderer, &r);
		SDL_RenderDrawRect(Util::get()->renderer, &r);
	}

	void setXY(int x, int y) {
		this->x = x;
		this->y = y;
		spriteSheet->follow(x, y);
	}
	void setDirXy(int x, int y) {
		dirX = x;
		dirY = y;
	}

	int getDirX() { return dirX; }
	int getDirY() { return dirY; }
};

