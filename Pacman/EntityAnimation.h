#pragma once
#include <SDL.h>
#include <string>

#include "Texture.h"
#include "Helper\Timer.h"

class EntityAnimation
{
public:
	EntityAnimation();
	~EntityAnimation();

	void init(std::string texturePath, int animFrameNum, float animFrameTime, SDL_Renderer* renderer, float scale);
	void draw(SDL_Renderer* renderer, int x, int y, double rotation);
	void setTextureColor(Uint32 r, Uint32 g, Uint32 b);
	void free();

	int getWidth();
	int getHeight();
	bool isAnimationOver();

private:
	Texture m_texture;
	Timer m_frameTimer;
	
	int m_animFrameNum;
	float m_animFrameTime;
	int m_currentFrame;

	float m_scale;

	SDL_Rect* m_spriteClips;
};

