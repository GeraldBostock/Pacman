#pragma once
#include <SDL.h>
#include <stdio.h>

#include "Texture.h"
#include "Entities\Pacman.h"

class Board
{
public:
	Board();
	~Board();

	void init(int windowWidth, int windowHeight, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer, bool debugMode);
	void updatePacman(Pacman* pacman, SDL_Renderer* renderer);
	void updateGhost(int posX, int posY, int width, int height, SDL_Renderer* renderer);
	void prepare();
	bool isInCenterOfTile(BaseEntity* entity);

	int getAppleCount();

	int getTileWidth();
	int getTileHeight();

private:
	int m_board[18][32];
	bool m_apples[18][32];
	int m_tileWidth = 40;
	int m_tileHeight = 40;

	int m_tileNumX;
	int m_tileNumY;

	int m_applesNum;

	Texture m_apple;
};

