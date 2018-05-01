#include "Ghost.h"



Ghost::Ghost()
{
	m_r = 255;
	m_g = 255;
	m_b = 255;
	m_directionTimer.start();
	m_timeBetweenDirectionChanges = rand() % 4 + 1;
	m_currentAnim = &m_moveAnimation;
	m_currentState = ALIVE;
}


Ghost::~Ghost()
{
}

void Ghost::loadScaredAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale)
{
	m_scaredAnim.init(texturePath, animFrames, timeBetweenFrames, renderer, scale);
}

void Ghost::loadDeadAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale)
{
	m_deadAnim.init(texturePath, animFrames, timeBetweenFrames, renderer, scale);
}

void Ghost::draw(SDL_Renderer* renderer)
{
	m_currentAnim->draw(renderer, m_posX, m_posY, 0);
}

void Ghost::initColors(Uint32 r, Uint32 g, Uint32 b)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_currentAnim->setTextureColor(m_r, m_g, m_b);
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

void Ghost::fear()
{
	m_currentAnim = &m_scaredAnim;
	m_currentAnim->setTextureColor(255, 255, 255);
}

void Ghost::die()
{
	m_currentAnim = &m_deadAnim;
	m_currentAnim->setTextureColor(m_r, m_g, m_b);
	m_currentState = DEAD;
}

void Ghost::powerUpOver()
{
	if (m_currentState == ALIVE)
	{
		m_currentAnim = &m_moveAnimation;
		m_currentAnim->setTextureColor(m_r, m_g, m_b);
	}
}

EntityState Ghost::getState()
{
	return m_currentState;
}