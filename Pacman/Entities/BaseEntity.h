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

	int getPosX();
	int getPosY();

	int getSpriteWidth();
	int getSpriteHeight();
	
	int* getNextCoordinates();
	int getSpeed();

	directions getDirection();
	directions getNextDirection();

	void setCanMove(bool canMove);
	void setCurrentTile(int i, int j);

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
	directions m_nextDirection;
	bool m_canMove;

	float m_timeBetweenAnimFrames;

	int m_currentTile[2];
	SDL_Rect* m_clipSprites;
private:
};

