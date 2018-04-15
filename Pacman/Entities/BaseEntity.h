#pragma once
#include <SDL.h>

#include "..\Helper\Timer.h"
#include "..\Texture.h"
#include "..\Input.h"

class BaseEntity
{
public:
	BaseEntity();
	~BaseEntity();

	void init(int x, int y, std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float m_scale);
	void loadMedia(std::string texturePath, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	void update();

protected:
	Texture m_texture;
	Timer m_frameTimer;
	Input m_input;

	int m_posX;
	int m_posY;
	int m_animFrameNum;
	int m_currentAnimFrame;
	int m_speed;
	int m_spriteWidth;
	int m_spriteHeight;
	double m_rotation;
	float m_scale;
	directions m_direction;

	float m_timeBetweenAnimFrames;

	SDL_Rect m_hitbox;
	SDL_Rect* m_clipSprites;
private:
};

