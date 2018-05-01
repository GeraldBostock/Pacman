#pragma once
#include <SDL.h>

#include "..\Helper\Timer.h"
#include "..\Texture.h"
#include "..\Input.h"
#include "IEntity.h"
#include "..\EntityAnimation.h"

enum EntityState
{
	ALIVE,
	DEAD
};

class BaseEntity : public IEntity
{
public:
	BaseEntity();
	~BaseEntity();

	void init(int x, int y);
	void loadAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale);
	virtual void handleInput(SDL_Event e);
	virtual void update(int screenWidth, int screenHeight, bool canChangeDirection, bool willCollide);
	virtual void draw(SDL_Renderer* renderer);
	virtual void free();
	virtual void fear() {}
	virtual void die() {}
	virtual void powerUpOver() {}
	virtual void blink() {}
	virtual EntityState getState();

	int getPosX();
	int getPosY();

	void setPosX(int posX);
	void setPosY(int posY);

	int getSpriteWidth();
	int getSpriteHeight();
	
	int* getNextCoordinates();
	int getSpeed();

	directions getDirection();
	directions getNextDirection();

	void setCollisionState(bool isColliding);
	void setCanMove(bool canMove);
	void setCurrentTile(int i, int j);

protected:
	EntityAnimation m_moveAnimation;

	Input m_input;

	int m_posX;
	int m_posY;
	int m_speed;
	int m_spriteWidth;
	int m_spriteHeight;
	double m_rotation;
	float m_scale;
	directions m_direction;
	directions m_nextDirection;
	bool m_canMove;
	bool m_isColliding;

	int m_currentTile[2];
private:
};

