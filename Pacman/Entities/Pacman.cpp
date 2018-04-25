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

void Pacman::update(int screenWidth, int screenHeight, bool canChangeDirection, bool isColliding)
{
	if (m_nextDirection != OTHER && canChangeDirection)
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
