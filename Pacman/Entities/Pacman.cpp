#include "Pacman.h"



Pacman::Pacman()
{
	m_direction = OTHER;
	m_nextDirection = OTHER;
	m_rotationAngle = 0.0;
	m_currentAnimation = &m_moveAnimation;
}


Pacman::~Pacman()
{
}

void Pacman::loadDeathAnimation(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale)
{
	m_deathAnimation.init(texturePath, animFrames, timeBetweenFrames, renderer, scale);
}

void Pacman::loadPowerUpAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale)
{
	m_poweredUp.init(texturePath, animFrames, timeBetweenFrames, renderer, scale);
}

void Pacman::loadBlinkAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale)
{
	m_blinkAnim.init(texturePath, animFrames, timeBetweenFrames, renderer, scale);
}

void Pacman::update(int screenWidth, int screenHeight, bool canChangeDirection, bool canMove)
{
	if (m_nextDirection != OTHER && canChangeDirection)
	{
		m_direction = m_nextDirection;
		m_nextDirection = OTHER;
	}

	if (!canMove)
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

void Pacman::draw(SDL_Renderer* renderer)
{
	m_currentAnimation->draw(renderer, m_posX, m_posY, m_rotation);
}

void Pacman::die()
{
	m_currentAnimation = &m_deathAnimation;
	m_rotation = 0;
}

void Pacman::revive()
{
	m_currentAnimation = &m_moveAnimation;
	m_direction = OTHER;
}

bool Pacman::isAnimationOver()
{
	return m_currentAnimation->isAnimationOver();
}

void Pacman::powerUp()
{
	m_currentAnimation = &m_poweredUp;
}

void Pacman::powerUpOver()
{
	m_currentAnimation = &m_moveAnimation;
}

void Pacman::blink()
{
	m_currentAnimation = &m_blinkAnim;
}

void Pacman::free()
{
	m_moveAnimation.free();
	m_deathAnimation.free();
}