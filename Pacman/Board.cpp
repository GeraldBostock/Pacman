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
			int hello = rand() % 7;

			if( hello != 0 ) m_board[j][i] = EMPTY;
			else m_board[j][i] = WALL;

			if(m_board[j][i] == WALL) m_apples[j][i] = false;
			else m_apples[j][i] = true;
		}
	}

	m_apple.loadFromFile("apple.png", renderer, 0.065f);
	m_wall.loadFromFile("wall.png", renderer, 0.25f);
}

void Board::prepare()
{
	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			m_collisions.clear();
		}
	}
}

void Board::updatePacman(BaseEntity* pacman)
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
				tileEntityCollision collision = { i * m_tileWidth , j * m_tileHeight , 1 };
				m_collisions.push_back(collision);
				//m_board[j][i] = 1;
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

void Board::updateGhost(BaseEntity* ghost)
{
	int posX = ghost->getPosX();
	int posY = ghost->getPosY();
	int width = ghost->getSpriteWidth();
	int height = ghost->getSpriteHeight();

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
				tileEntityCollision collision = { i * m_tileWidth , j * m_tileHeight , 2 };
				m_collisions.push_back(collision);
				//m_board[j][i] = 2;
			}
		}
	}
}

void Board::draw(SDL_Renderer* renderer, bool debugMode)
{
	if (debugMode)
	{
		for (int i = 0; i < m_collisions.size(); i++)
		{
			tileEntityCollision collision = m_collisions.at(i);
			SDL_Rect rect = { collision.posX, collision.posY, m_tileWidth, m_tileHeight };
			if (collision.entityType == 1)
			{
				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			}
			else if (collision.entityType == 2) SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			if (debugMode)
			{
				SDL_Rect rect = { i * m_tileWidth, j * m_tileHeight, m_tileWidth, m_tileHeight };
				/*if (m_board[j][i] == 1)
				{
					SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
				else if (m_board[j][i] == 2)
				{
					SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
					SDL_RenderFillRect(renderer, &rect);
				}*/
				SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
				SDL_RenderDrawRect(renderer, &rect);
			}

			if (m_board[j][i] == WALL)
			{
				m_wall.draw(i * m_tileWidth, j * m_tileHeight, renderer, NULL, 0);
			}

			//Draw the apple. +2 and +1 are there to center the apple inside the tile but this feels wrong. This happens because apples are square but tiles are not.
			//Make the tiles squares mate
			if (m_apples[j][i]) m_apple.draw(i * m_tileWidth +16, j * m_tileHeight + 16, renderer, NULL, 0.0);
		}
	}
}

bool Board::canMove(BaseEntity* entity, int screenWidth, int screenHeight)
{
	if (!isInCenterOfTile(entity)) return false;
	else
	{
		int entityX = entity->getPosX();
		int entityY = entity->getPosY();
		int entityWidth = entity->getSpriteWidth();
		int entityHeight = entity->getSpriteHeight();
		directions direction = entity->getDirection();

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
					if (entityX == i * m_tileWidth + 4 && entityY == j * m_tileHeight + 4)
					{
						switch (direction)
						{
						case RIGHT:
							if (m_board[j][(i + 1 + m_tileNumX) % m_tileNumX] != WALL) return false;
							break;
						case LEFT:
							if (m_board[j][(i - 1 + m_tileNumX) % m_tileNumX] != WALL) return false;
							break;
						case DOWN:
							if (m_board[(j + 1 + m_tileNumY) % m_tileNumY][i] != WALL) return false;
							break;
						case UP:
							if (m_board[(j - 1 + m_tileNumY) % m_tileNumY][i] != WALL) return false;
							break;
						default:
							return true;
							break;
						}
					}
				}
			}
		}
	}

	return true;

	/*int entityX = entity->getPosX();
	int entityY = entity->getPosY();
	int entityWidth = entity->getSpriteWidth();
	int entityHeight = entity->getSpriteHeight();
	int speed = entity->getSpeed();
	directions direction = entity->getDirection();

	switch (direction)
	{
	case RIGHT:
		entityX = (entityX + (speed + 2) + screenWidth) % screenWidth;
		break;
	case LEFT:
		entityX = (entityX - (speed + 2) + screenWidth) % screenWidth;
		break;
	case UP:
		entityY = (entityY - (speed + 2) + screenHeight) % screenHeight;
		break;
	case DOWN:
		entityY = (entityY + (speed + 2) + screenHeight) % screenHeight;
		break;
	default:
		break;
	}

	if (entityX + entityWidth > screenWidth) entityX = 0;
	if (entityY + entityHeight > screenHeight) entityY = 0;

	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			SDL_Rect boardRect = { i * m_tileWidth, j * m_tileHeight, m_tileWidth, m_tileHeight };
			SDL_Rect entityRect = { entityX, entityY, entityWidth, entityHeight };
			SDL_Rect resultRect;

			SDL_bool result = SDL_IntersectRect(&boardRect, &entityRect, &resultRect);
			if (result == SDL_TRUE && m_board[j][i] == 1) return true;
		}
	}

	return false;*/
}

bool Board::canTurn(BaseEntity* entity)
{
	int entityX = entity->getPosX();
	int entityY = entity->getPosY();
	int entityWidth = entity->getSpriteWidth();
	int entityHeight = entity->getSpriteHeight();
	directions nextDirection = entity->getNextDirection();

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
				if (entityX == i * m_tileWidth + 4 && entityY == j * m_tileHeight + 4)
				{
					switch (nextDirection)
					{
					case RIGHT:
						if (m_board[j][(i + 1 + m_tileNumX) % m_tileNumX] != WALL) return true;
						break;
					case LEFT:
						if (m_board[j][(i - 1 + m_tileNumX) % m_tileNumX] != WALL) return true;
						break;
					case DOWN:
						if (m_board[(j + 1 + m_tileNumY) % m_tileNumY][i] != WALL) return true;
						break;
					case UP:
						if (m_board[(j - 1 + m_tileNumY) % m_tileNumY][i] != WALL) return true;
						break;
					default:
						return true;
						break;
					}
				}
			}
		}
	}

	return false;
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
