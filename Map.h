#pragma once
#include "SpriteSheet.h"
class Map {
	SpriteSheet* sheet;
	
public:

	Map() {
		sheet = new SpriteSheet("assets/map.png", 1, 1, 1, Util::get()->WIDTH, Util::get()->HEIGHT);
		sheet->setLoop(0, 1, 0);
	}

	void draw() {
		sheet->draw();
	}


};