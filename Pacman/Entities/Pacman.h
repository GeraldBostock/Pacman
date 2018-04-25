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

	void update(int screenWidth, int screenHeight, bool canChangeDirection, bool isColliding) override;

private:
	float m_rotationAngle;
};

