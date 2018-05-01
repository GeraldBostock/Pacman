#include "Board.h"



Board::Board()
{
	m_ghostsNum = 0;
	m_applesNum = 0;
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

	m_board[2][0] = PACMAN_SPAWN;

	m_board[0][0] = GHOST_SPAWN;
	m_board[5][0] = GHOST_SPAWN;
	m_board[10][0] = GHOST_SPAWN;

	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			if (m_board[j][i] == PACMAN_SPAWN)
			{
				m_pacmanStartPos = { i * m_tileWidth + 4, j * m_tileHeight + 4 };
			}
			else if (m_board[j][i] == GHOST_SPAWN)
			{
				Position ghostPosition = { i * m_tileWidth + 4, j * m_tileHeight + 4 };
				m_ghostsStartPos.push_back(ghostPosition);
				m_ghostsNum++;
			}
		}
	}

	m_apple.loadFromFile("apple.png", renderer, 0.065f);
	m_wall.loadFromFile("wall.png", renderer, 0.25f);
}

void Board::initFromFile(std::string filePath, SDL_Renderer* renderer)
{
	printf("Reading from file: %s\n", filePath.c_str());
	std::ifstream infile(filePath);
	int i = 0;

	std::vector<std::string> mapFile;
	std::string line;

	while (std::getline(infile, line))
	{
		mapFile.push_back(line);
	}

	printf("File length: %d\n", mapFile.size());

	m_tileWidth = std::stoi(mapFile.at(0));
	m_tileHeight = std::stoi(mapFile.at(1));
	m_tileNumX = std::stoi(mapFile.at(2));
	m_tileNumY = std::stoi(mapFile.at(3));

	printf("Tile width: %d\nTile height: %d\nNumber of tiles at X: %d\nNumber of tiles at Y: %d\n", m_tileWidth, m_tileHeight, m_tileNumX, m_tileNumY);

	for (int i = 0; i < m_tileNumX; i++)
	{
		std::string line = mapFile.at(i + 4);

		for(int j = 0; j < m_tileNumY; j++)
		{
			int value = line[j] - '0';
			switch (value)
			{
			case 0:
				m_board[j][i] = EMPTY;
				m_apples[j][i] = false;
				break;
			case 1:
				m_board[j][i] = WALL;
				m_apples[j][i] = false;
				break;
			case 2:
				m_board[j][i] = PACMAN_SPAWN;
				m_apples[j][i] = false;
				break;
			case 3:
				m_board[j][i] = GHOST_SPAWN;
				m_apples[j][i] = false;
				break;
			case 4:
				m_board[j][i] = EMPTY;
				m_apples[j][i] = true;
				m_applesNum++;
				break;
			case 5:
				m_board[j][i] = EMPTY;
				m_apples[j][i] = 2;
				break;
			default:
				m_board[j][i] = EMPTY;
				m_apples[j][i] = false;
				break;
			}
		}
	}

	printf("Done reading tiles. Starting reading tile colors\n");

	for (int i = 0; i < m_tileNumX; i++)
	{
		std::string line = mapFile.at(i + m_tileNumX + 4);

		for (int j = 0; j < m_tileNumY; j++)
		{
			m_tileColors[j][i] = line[j] - '0';
		}
	}

	printf("Done reading tile colors\n");

	for (int i = 0; i < m_tileNumX; i++)
	{
		for (int j = 0; j < m_tileNumY; j++)
		{
			if (m_board[j][i] == PACMAN_SPAWN)
			{
				m_pacmanStartPos = { i * m_tileWidth + 4, j * m_tileHeight + 4 };
				printf("Spawning player at (%d, %d)\n", m_pacmanStartPos.x, m_pacmanStartPos.y);
			}
			else if (m_board[j][i] == GHOST_SPAWN)
			{
				Position ghostPosition = { i * m_tileWidth + 4, j * m_tileHeight + 4 };
				m_ghostsStartPos.push_back(ghostPosition);

				printf("Spawning ghost #%d at (%d, %d)\n", m_ghostsNum, ghostPosition.x, ghostPosition.y);

				m_ghostsNum++;
			}
		}
	}

	m_apple.loadFromFile("Assets/apple.png", renderer, 0.065f);
	m_wall.loadFromFile("Assets/wall.png", renderer, 0.25f);
	m_powerup.loadFromFile("Assets/powerup.png", renderer, 0.7f);
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

bool Board::updatePacman(BaseEntity* pacman)
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

			if (result == SDL_TRUE && m_apples[j][i] == 1)
			{
				m_apples[j][i] = false;
				m_applesNum--;
				return false;
			}
			else if (result == SDL_TRUE && m_apples[j][i] == 2)
			{
				m_apples[j][i] = false;
				return true;
			}
		}
	}

	return false;
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
			}
		}
	}
}

void Board::draw(SDL_Renderer* renderer, bool debugMode)
{
	if (debugMode)
	{
		for (unsigned int i = 0; i < m_collisions.size(); i++)
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
				SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
				SDL_RenderDrawRect(renderer, &rect);
			}

			if (m_board[j][i] == WALL)
			{
				setTileColor(m_tileColors[j][i]);
				m_wall.draw(i * m_tileWidth, j * m_tileHeight, renderer, NULL, 0);
			}

			//Draw the apple. +2 and +1 are there to center the apple inside the tile but this feels wrong. This happens because apples are square but tiles are not.
			//Make the tiles squares mate
			if (m_apples[j][i] == 1) m_apple.draw(i * m_tileWidth +16, j * m_tileHeight + 16, renderer, NULL, 0.0);
			else if (m_apples[j][i] == 2) m_powerup.draw(i * m_tileWidth + 10, j * m_tileHeight + 10, renderer, NULL, 0);
		}
	}

	SDL_Rect borderRect = { 0, 0, 1320, 760 };
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderDrawRect(renderer, &borderRect);
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

void Board::setTileColor(int color)
{
	switch (color)
	{
	case 0:
		m_wall.setColor(100, 100, 100);
		break;
	case 1:
		m_wall.setColor(200, 0, 0);
		break;
	case 2:
		m_wall.setColor(0, 200, 0);
		break;
	case 3:
		m_wall.setColor(0, 0, 200);
		break;
	case 4:
		m_wall.setColor(225, 225, 225);
		break;
	case 5:
		m_wall.setColor(225, 100, 0);
		break;
	case 6:
		m_wall.setColor(225, 225, 0);
		break;
	case 7:
		m_wall.setColor(255, 51, 153);
		break;
	default:
		break;
	}
}

Position Board::getPacmanStartPos()
{
	return m_pacmanStartPos;
}

std::vector<Position>* Board::getGhostsStartPos()
{
	return &m_ghostsStartPos;
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
