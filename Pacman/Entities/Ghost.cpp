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

void Ghost::handleInput(SDL_Event e)
{
	if (m_directionTimer.getTicks() / 1000.f > 1)
	{
		directions direction = static_cast<directions>(rand() % OTHER);
		m_nextDirection = direction;
		m_directionTimer.start();
	}
}
