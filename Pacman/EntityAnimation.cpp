#include "EntityAnimation.h"



EntityAnimation::EntityAnimation()
{
}


EntityAnimation::~EntityAnimation()
{
}

void EntityAnimation::init(std::string texturePath, int animFrameNum, float animFrameTime, SDL_Renderer* renderer, float scale)
{
	m_animFrameNum = animFrameNum;
	m_currentFrame = 0;
	m_animFrameTime = animFrameTime;
	m_scale = scale;

	m_texture.loadFromFile(texturePath, renderer, scale);

	m_spriteClips = new SDL_Rect[m_animFrameNum];

	for (int i = 0; i < m_animFrameNum; i++)
	{
		m_spriteClips[i].x = i * m_texture.getOrigWidth() / m_animFrameNum;
		m_spriteClips[i].y = 0;
		m_spriteClips[i].w = m_texture.getOrigWidth() / m_animFrameNum;
		m_spriteClips[i].h = m_texture.getOrigWidth() / m_animFrameNum;
	}

	m_frameTimer.start();
}

void EntityAnimation::draw(SDL_Renderer* renderer, int x, int y, double rotation)
{
	SDL_Rect* currentClip = &m_spriteClips[m_currentFrame];
	m_texture.draw(x, y, renderer, currentClip, rotation);

	if (m_frameTimer.getTicks() / 1000.f > m_animFrameTime)
	{
		m_currentFrame++;
		m_frameTimer.start();
	}

	if (m_currentFrame >= m_animFrameNum) m_currentFrame = 0;
}

bool EntityAnimation::isAnimationOver()
{
	if (m_currentFrame == 0) return true;
	else return false;
}

void EntityAnimation::setTextureColor(Uint32 r, Uint32 g, Uint32 b)
{
	m_texture.setColor(r, g, b);
}

int EntityAnimation::getWidth()
{
	return m_texture.getWidth() / m_animFrameNum;
}

int EntityAnimation::getHeight()
{
	return  m_texture.getHeight();
}

void EntityAnimation::free()
{
	m_texture.free();
}
