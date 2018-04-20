#include "Ghost.h"



Ghost::Ghost()
{
	m_r = 255;
	m_g = 255;
	m_b = 255;
	m_directionTimer.start();
	m_timeBetweenDirectionChanges = rand() % 4 + 1;
}


Ghost::~Ghost()
{
}

void Ghost::draw(SDL_Renderer* renderer)
{
	SDL_Rect* currentClip = &m_clipSprites[m_currentAnimFrame / m_animFrameNum];
	m_texture.setColor(m_r, m_g, m_b);
	m_texture.draw(m_posX, m_posY, renderer, currentClip, m_rotation);

	if (m_frameTimer.getTicks() / 1000.f > m_timeBetweenAnimFrames)
	{
		m_currentAnimFrame++;
		m_frameTimer.start();
	}

	if (m_currentAnimFrame / m_animFrameNum >= m_animFrameNum) m_currentAnimFrame = 0;
}

void Ghost::initColors(Uint32 r, Uint32 g, Uint32 b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

void Ghost::update(int screenWidth, int screenHeight, bool canMove, bool willCollide)
{
	if (m_directionTimer.getTicks() / 1000.f > 1)
	{
		directions direction = static_cast<directions>(rand() % OTHER);
		m_nextDirection = direction;
		m_directionTimer.start();
	}

	if (canMove && m_nextDirection != OTHER)
	{
		m_direction = m_nextDirection;
		m_nextDirection = OTHER;
	}

	if (!willCollide)
	{
		switch (m_direction)
		{
		case RIGHT:
			m_posX += m_speed;
			break;
		case LEFT:
			m_posX -= m_speed;
			break;
		case DOWN:
			m_posY += m_speed;
			break;
		case UP:
			m_posY -= m_speed;
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
