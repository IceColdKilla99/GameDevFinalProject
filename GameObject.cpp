#include "GameObject.h"


GameObject::GameObject(int x, int y, int speed, SpriteSheet* sheet, TYPE type, int life)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	spriteSheet = sheet;
	this->type = type;
	this->life = life;
}

void GameObject::draw()
{
	spriteSheet->playAnimation();
	spriteSheet->follow(x, y);
	spriteSheet->draw();
}

int GameObject::getX()
{
	return x;
}

int GameObject::getY()
{
	return y;
}

bool GameObject::moveTo(int toX, int toY)
{
	float disc = point_distance(x, y, toX, toY);

	float normalizedX = (toX - x) / disc;
	float normalizedY = (toY - y) / disc;

	if (disc > 5) {
		x += normalizedX * speed;
		y += normalizedY * speed;
		return false;
	}
	return true;
}

float GameObject::point_distance(int x1, int y1, int x2, int y2)
{
	// Calculating distance
	return sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) * 1.0);
}

bool GameObject::checkCollide(GameObject* obj)
{

	SDL_Rect a = getRect();
	SDL_Rect b = obj->getRect();

	if (a.x < b.x + b.w &&
		a.x + a.w > b.x &&
		a.y < b.y + b.h &&
		a.h + a.y > b.y) {
		return true;
	}
	return false;
}

bool GameObject::checkClickCollide(SDL_Rect a,int x, int y)
{
	if (x >= a.x && x <= a.x + a.w 
		&& y >= a.y && y <= a.y + a.h) {
		return true;
	}
	return false;
}

bool GameObject::isDead()
{
	return isAlive == false;
}
