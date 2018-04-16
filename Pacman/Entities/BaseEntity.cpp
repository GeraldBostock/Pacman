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
		m_clipSprites[i].x = i * 128;
		m_clipSprites[i].y = 0;
		m_clipSprites[i].w = 128;
		m_clipSprites[i].h = 128;
	}
}

void BaseEntity::update()
{
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