#pragma once
#include <SDL.h>

enum directions {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	OTHER
};

class Input
{
	bool KEYS[322];

public:
	Input();
	~Input();

	directions getInput(SDL_Event e);
};

