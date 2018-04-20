#include "Pacman.h"



Pacman::Pacman()
{
	m_direction = RIGHT;
	m_nextDirection = OTHER;
	m_rotationAngle = 0.0;
}


Pacman::~Pacman()
{
}

void Pacman::handleInput(SDL_Event e, bool canMove)
{
	directions input = m_input.getInput(e);
	if(input != OTHER) m_nextDirection = input;
	/*if (input != OTHER && canMove) m_direction = input;
	else if (input != OTHER && !canMove) m_nextDirection = input;*/
}

void Pacman::update(int screenWidth, int screenHeight, int tileWidth, int tileHeight, bool canMove, bool isColliding)
{
	if (m_nextDirection != OTHER && canMove)
	{
		m_direction = m_nextDirection;
		m_nextDirection = OTHER;
	}

	if (!isColliding)
	{
		switch (m_direction)
		{
		case RIGHT:
			m_posX += m_speed;
			m_rotation = 0.0;
			break;
		case LEFT:
			m_posX -= m_speed;
			m_rotation = 180.0;
			break;
		case DOWN:
			m_posY += m_speed;
			m_rotation = 90.0;
			break;
		case UP:
			m_posY -= m_speed;
			m_rotation = 270.0;
			break;
		default:
			break;
		}
	}

	if (m_posX + m_spriteWidth < 0) m_posX = screenWidth;
	else if (m_posX > screenWidth) m_posX = -m_spriteWidth;
	else if (m_posY + 64 < 0) m_posY = screenHeight;
	else if (m_posY > screenHeight) m_posY = -m_spriteHeight;
}
