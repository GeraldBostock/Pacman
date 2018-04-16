#include "Board.h"



Board::Board()
{
}


Board::~Board()
{
}

void Board::init(int windowWidth, int windowHeight, SDL_Renderer* renderer)
{
	m_tileNumX = windowWidth / m_tileWidth;
	m_tileNumY = windowHeight / m_tileHeight;

	m_applesNum = m_tileNumX * m_tileNumY;

	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			m_board[j][i] = 0;
			m_apples[j][i] = true;
		}
	}

	m_apple.loadFromFile("apple.png", renderer, 0.065f);
}

void Board::prepare()
{
	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			m_board[j][i] = 0;
		}
	}
}

void Board::updatePacman(Pacman* pacman, SDL_Renderer* renderer)
{
	int posX = pacman->getPosX();
	int posY = pacman->getPosY();
	int width = pacman->getSpriteWidth();
	int height = pacman->getSpriteHeight();

	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			SDL_Rect boardRect = { i * m_tileWidth, j * m_tileHeight, m_tileWidth, m_tileHeight };
			SDL_Rect pacmanRect = { posX, posY, width, height };
			SDL_Rect resultRect;

			//Tile-Entity collision
			SDL_bool result = SDL_IntersectRect(&boardRect, &pacmanRect, &resultRect);
			if (result == SDL_TRUE)
			{
				m_board[j][i] = 1;
			}

			//Pacman-Apple collision
			SDL_Rect appleRect = { i * m_tileWidth + 16, j * m_tileHeight + 16, m_apple.getWidth(), m_apple.getHeight() };
			SDL_Rect pacmanMouth = { posX + width / 4, posY + height / 4, width / 2, height / 2 };

			result = SDL_IntersectRect(&appleRect, &pacmanMouth, &resultRect);

			if (result == SDL_TRUE && m_apples[j][i])
			{
				m_apples[j][i] = false;
				m_applesNum--;
			}
		}
	}
}

void Board::updateGhost(int posX, int posY, int width, int height, SDL_Renderer* renderer)
{
	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			SDL_Rect boardRect = { i * m_tileWidth, j * m_tileHeight, m_tileWidth, m_tileHeight };
			SDL_Rect pacmanRect = { posX, posY, width, height };
			SDL_Rect resultRect;

			//Tile-Entity collision
			SDL_bool result = SDL_IntersectRect(&boardRect, &pacmanRect, &resultRect);
			if (result == SDL_TRUE)
			{
				m_board[j][i] = 2;
			}
		}
	}
}

void Board::draw(SDL_Renderer* renderer, bool debugMode)
{
	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			if (debugMode)
			{
				SDL_Rect rect = { i * m_tileWidth, j * m_tileHeight, m_tileWidth, m_tileHeight };
				if (m_board[j][i] == 1)
				{
					SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				else if (m_board[j][i] == 2)
				{
					SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
				SDL_RenderDrawRect(renderer, &rect);
			}

			//Draw the apple. +2 and +1 are there to center the apple inside the tile but this feels wrong. This happens because apples are square but tiles are not.
			//Make the tiles squares mate
			if (m_apples[j][i]) m_apple.draw(i * m_tileWidth +16, j * m_tileHeight + 16, renderer, NULL, 0.0);
		}
	}
}

bool Board::isInCenterOfTile(BaseEntity* entity)
{
	int entityX = entity->getPosX();
	int entityY = entity->getPosY();
	int entityWidth = entity->getSpriteWidth();
	int entityHeight = entity->getSpriteHeight();

	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			SDL_Rect boardRect = { i * m_tileWidth, j * m_tileHeight, m_tileWidth, m_tileHeight };
			SDL_Rect entityRect = { entityX, entityY, entityWidth, entityHeight };
			SDL_Rect resultRect;

			SDL_bool result = SDL_IntersectRect(&boardRect, &entityRect, &resultRect);
			if (result == SDL_TRUE)
			{
				if (entityX == i * m_tileWidth + 4 && entityY == j * m_tileHeight + 4) return true;
			}
		}
	}

	return false;
}

int Board::getAppleCount()
{
	return m_applesNum;
}

int Board::getTileWidth()
{
	return m_tileWidth;
}

int Board::getTileHeight()
{
	return m_tileHeight;
}
