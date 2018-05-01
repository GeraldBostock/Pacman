#pragma once
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#include "Texture.h"
#include "Entities\Pacman.h"

enum Colors
{
	GRAY,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA
};

struct tileEntityCollision
{
	int posX;
	int posY;
	int entityType;
};

struct Position
{
	int x;
	int y;
};

enum Tiles
{
	EMPTY,
	WALL,
	PACMAN_SPAWN,
	GHOST_SPAWN,
	LAST
};

class Board
{
public:
	Board();
	~Board();

	void init(int windowWidth, int windowHeight, SDL_Renderer* renderer);
	void initFromFile(std::string filePath, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer, bool debugMode);
	bool updatePacman(BaseEntity* pacman);
	void updateGhost(BaseEntity* ghost);
	void prepare();
	bool isInCenterOfTile(BaseEntity* entity);
	bool canMove(BaseEntity* entity, int screenWidth, int screenHeight);
	bool canTurn(BaseEntity* entity);

	Position getPacmanStartPos();
	std::vector<Position>* getGhostsStartPos();

	int getAppleCount();

	int getTileWidth();
	int getTileHeight();

private:
	Tiles m_board[19][33];
	int m_tileColors[19][33];
	unsigned char m_apples[19][33];
	int m_tileWidth = 40;
	int m_tileHeight = 40;

	int m_tileNumX;
	int m_tileNumY;

	int m_applesNum;

	int m_ghostsNum;
	Position m_pacmanStartPos;
	std::vector<Position> m_ghostsStartPos;

	std::vector<tileEntityCollision> m_collisions;

	Texture m_apple;
	Texture m_wall;
	Texture m_powerup;

	void setTileColor(int color);
};

