#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

directions Input::getInput(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			return UP;
		case SDLK_DOWN:
			return DOWN;
		case SDLK_LEFT:
			return LEFT;
		case SDLK_RIGHT:
			return RIGHT;
		default:
			break;
		}
	}

	return OTHER;
}
