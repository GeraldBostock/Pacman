#include "BaseEntity.h"



BaseEntity::BaseEntity()
{
	m_speed = 4;
	m_rotation = 0.0;
	m_direction = RIGHT;
}


BaseEntity::~BaseEntity()
{
}

void BaseEntity::init(int x, int y)
{
	m_posX = x;
	m_posY = y;
}


void BaseEntity::loadAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale)
{
	m_moveAnimation.init(texturePath, animFrames, timeBetweenFrames, renderer, scale);
	m_spriteWidth = m_moveAnimation.getWidth();
	m_spriteHeight = m_moveAnimation.getHeight();
}

void BaseEntity::handleInput(SDL_Event e)
{
	directions input = m_input.getInput(e);
	if (input != OTHER) m_nextDirection = input;
}

void BaseEntity::update(int screenWidth, int screenHeight, bool canChangeDirection, bool willCollide)
{
	if (m_nextDirection != OTHER && canChangeDirection)
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

void BaseEntity::draw(SDL_Renderer* renderer)
{
	m_moveAnimation.draw(renderer, m_posX, m_posY, 0);
}

int BaseEntity::getPosX()
{
	return m_posX;
}

int BaseEntity::getPosY()
{
	return m_posY;
}

int BaseEntity::getSpriteWidth()
{
	return m_spriteWidth;
}

int BaseEntity::getSpriteHeight()
{
	return m_spriteHeight;
}

void BaseEntity::setCanMove(bool canMove)
{
	m_canMove = canMove;
}

directions BaseEntity::getDirection()
{
	return m_direction;
}

int* BaseEntity::getNextCoordinates()
{
	int nextX = m_posX;
	int nextY = m_posY;

	switch (m_direction)
	{
	case RIGHT:
		nextX += m_speed;
		break;
	case LEFT:
		nextX -= m_speed;
		break;
	case DOWN:
		nextY += m_speed;
		break;
	case UP:
		nextY -= m_speed;
		break;
	default:
		break;
	}

	int coords[2];
	coords[0] = nextX;
	coords[1] = nextY;

	return coords;
}

void BaseEntity::setCurrentTile(int i, int j)
{
	m_currentTile[0] = i;
	m_currentTile[1] = j;
}

int BaseEntity::getSpeed()
{
	return m_speed;
}

directions BaseEntity::getNextDirection()
{
	return m_nextDirection;
}

void BaseEntity::setCollisionState(bool isColliding)
{
	m_isColliding = isColliding;
}

void BaseEntity::setPosX(int posX)
{
	m_posX = posX;
}

void BaseEntity::setPosY(int posY)
{
	m_posY = posY;
}

void BaseEntity::free()
{
	m_moveAnimation.free();
}

EntityState BaseEntity::getState()
{
	return ALIVE;
}