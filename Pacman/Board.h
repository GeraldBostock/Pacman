#pragma once
#include <SDL.h>
#include <stdio.h>

#include "Texture.h"

class Board
{
public:
	Board();
	~Board();

	void init(int windowWidth, int windowHeight, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	void update(int posX, int posY, int width, int height, SDL_Renderer* renderer);

private:
	bool m_board[24][40];
	bool m_apples[24][40];
	int m_tileWidth = 32;
	int m_tileHeight = 30;

	int m_tileNumX;
	int m_tileNumY;

	Texture m_apple;
};

