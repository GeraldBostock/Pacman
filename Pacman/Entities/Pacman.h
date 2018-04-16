#pragma once
#include <SDL.h>

#include "..\Texture.h"
#include "..\Helper\Timer.h"
#include "BaseEntity.h"

class Pacman : public BaseEntity
{
public:
	Pacman();
	~Pacman();

	void handleInput(SDL_Event e, bool canMove);
	void update(int screenWidth, int screenHeight, int tileWidth, int tileHeight, bool canMove);

private:
	float m_rotationAngle;
};

