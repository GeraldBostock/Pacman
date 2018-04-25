#pragma once
#include <SDL.h>
#include <string>

class IEntity
{
public:
	virtual ~IEntity() {}

	virtual void loadMedia(std::string texturePath, SDL_Renderer* renderer) = 0;
	virtual void handleInput(SDL_Event e) = 0;
	virtual void update(int screenWidth, int screenHeight, bool canChangeDirection, bool willCollide) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;
};

