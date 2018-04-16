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

	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			m_board[j][i] = false;
			m_apples[j][i] = true;
		}
	}

	m_apple.loadFromFile("apple.png", renderer, 0.065f);
}

void Board::update(int posX, int posY, int width, int height, SDL_Renderer* renderer)
{
	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			SDL_Rect boardRect = { i * m_tileWidth, j * m_tileHeight, m_tileWidth, m_tileHeight };
			SDL_Rect pacmanRect = { posX, posY, width, height };
			SDL_Rect resultRect;
			SDL_bool result = SDL_IntersectRect(&boardRect, &pacmanRect, &resultRect);

			if (result == SDL_TRUE)
			{
				m_board[j][i] = true;
			}
			else
			{
				m_board[j][i] = false;
			}

			SDL_Rect appleRect = { i * m_tileWidth + m_tileWidth / 3, j * m_tileHeight + m_tileHeight / 3, m_apple.getWidth(), m_apple.getHeight() };

			result = SDL_IntersectRect(&appleRect, &pacmanRect, &resultRect);

			if (result == SDL_TRUE) m_apples[j][i] = false;
		}
	}
}

void Board::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			SDL_Rect rect = { i * m_tileWidth, j * m_tileHeight, m_tileWidth, m_tileHeight };
			if (m_board[j][i])
			{
				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(renderer, &rect);

			if (m_apples[j][i]) m_apple.draw(i * m_tileWidth + m_tileWidth / 3 + 2, j * m_tileHeight + m_tileHeight / 3 + 1, renderer, NULL, 0.0);
		}
	}
}
