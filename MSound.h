#pragma once
#include <SDL_mixer.h>
#include<iostream>
#include "MSound.h"

class MSound {

	Mix_Music* gameMusic = NULL;
	Mix_Music* menuMusic = NULL;

	Mix_Chunk** sounds;

public:

	enum SOUNDNAME {
		THREE_SECONDS_LEFT = 0,
		SHOT = 1
	};

	MSound() {

		//Load Music
		menuMusic = Mix_LoadMUS("assets/sounds/menu.mid");
		gameMusic = Mix_LoadMUS("assets/sounds/game.mid");

		sounds = new Mix_Chunk*[5];

		// fx
		sounds[THREE_SECONDS_LEFT] = Mix_LoadWAV("assets/sounds/3secondsleft.wav");
		sounds[SHOT] = Mix_LoadWAV("assets/sounds/shot.wav");

		Mix_Volume(0,MIX_MAX_VOLUME);
	}

	void playMenuMusic() {
		Mix_PlayMusic(menuMusic, 0);
	}
	void playGameMusic() {
		Mix_PlayMusic(gameMusic, 0);
	}

	void playSound(SOUNDNAME id) {
		Mix_PlayChannel(-1, sounds[id], 0);
	}
};