#pragma once
#include <SDL.h>

enum directions {
	LEFT,
	RIGHT,
	UP,
	DOWN,
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

