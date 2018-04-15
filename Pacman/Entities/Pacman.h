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

	void handleInput(SDL_Event e);
	void update(int screenWidth, int screenHeight);

private:
	float m_rotationAngle;
};

