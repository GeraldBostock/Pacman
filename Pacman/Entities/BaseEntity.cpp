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

void BaseEntity::init(int x, int y, std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale)
{
	m_posX = x;
	m_posY = y;
	m_animFrameNum = animFrames;
	m_currentAnimFrame = 0;
	m_timeBetweenAnimFrames = timeBetweenFrames;
	m_scale = scale;
	loadMedia(texturePath, renderer);
	m_frameTimer.start();
}

void BaseEntity::loadMedia(std::string texturePath, SDL_Renderer* renderer)
{
	m_texture.loadFromFile(texturePath, renderer, m_scale);
	m_spriteWidth = m_texture.getWidth() / m_animFrameNum;
	m_spriteHeight = m_texture.getHeight();

	m_clipSprites = new SDL_Rect[m_animFrameNum];

	for (int i = 0; i < m_animFrameNum; i++)
	{
		m_clipSprites[i].x = i * m_texture.getOrigWidth() / m_animFrameNum;
		m_clipSprites[i].y = 0;
		m_clipSprites[i].w = m_texture.getOrigWidth() / m_animFrameNum;
		m_clipSprites[i].h = m_texture.getOrigWidth() / m_animFrameNum;
	}
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
	SDL_Rect* currentClip = &m_clipSprites[m_currentAnimFrame / m_animFrameNum];
	m_texture.draw(m_posX, m_posY, renderer, currentClip, m_rotation);

	if (m_frameTimer.getTicks() / 1000.f > m_timeBetweenAnimFrames)
	{
		m_currentAnimFrame++;
		m_frameTimer.start();
	}

	if (m_currentAnimFrame / m_animFrameNum >= m_animFrameNum) m_currentAnimFrame = 0;
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