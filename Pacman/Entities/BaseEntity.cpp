#include "BaseEntity.h"



BaseEntity::BaseEntity()
{
	m_speed = 3;
	m_rotation = 0.0;
}


BaseEntity::~BaseEntity()
{
}

void BaseEntity::init(int x, int y, std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames)
{
	m_posX = x;
	m_posY = y;
	m_animFrameNum = animFrames;
	m_currentAnimFrame = 0;
	m_timeBetweenAnimFrames = timeBetweenFrames;
	loadMedia(texturePath, renderer);
	m_frameTimer.start();
}

void BaseEntity::loadMedia(std::string texturePath, SDL_Renderer* renderer)
{
	m_texture.loadFromFile(texturePath, renderer, 0.25f);
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
