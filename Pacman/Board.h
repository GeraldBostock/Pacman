#pragma once
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <memory>

#include "Texture.h"
#include "Entities\Pacman.h"

struct tileEntityCollision
{
	int posX;
	int posY;
	int entityType;
};

enum Tiles
{
	EMPTY,
	WALL,
	LAST
};

class Board
{
public:
	Board();
	~Board();

	void init(int windowWidth, int windowHeight, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer, bool debugMode);
	void updatePacman(BaseEntity* pacman);
	void updateGhost(BaseEntity* ghost);
	void prepare();
	bool isInCenterOfTile(BaseEntity* entity);
	bool canMove(BaseEntity* entity, int screenWidth, int screenHeight);
	bool canTurn(BaseEntity* entity);

	int getAppleCount();

	int getTileWidth();
	int getTileHeight();

private:
	Tiles m_board[18][32];
	bool m_apples[18][32];
	int m_tileWidth = 40;
	int m_tileHeight = 40;

	int m_tileNumX;
	int m_tileNumY;

	int m_applesNum;

	std::vector<tileEntityCollision> m_collisions;

	Texture m_apple;
	Texture m_wall;
};

