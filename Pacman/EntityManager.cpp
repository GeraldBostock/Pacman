#include "EntityManager.h"



EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

std::vector<int> EntityManager::checkForGhostCollision(std::vector<BaseEntity*>* entities)
{
	std::vector<int> ghostIds;

	BaseEntity* pacman = entities->at(0);
	int pacmanPosX = pacman->getPosX();
	int pacmanPosY = pacman->getPosY();
	int pacmanWidth = pacman->getSpriteWidth();
	int pacmanHeight = pacman->getSpriteHeight();

	pacman->setCollisionState(false);

	SDL_Rect pacmanRect = { pacmanPosX, pacmanPosY, pacmanWidth, pacmanHeight };

	for (int i = 1; i < entities->size(); i++)
	{
		BaseEntity* ghost = entities->at(i);
		int ghostPosX = ghost->getPosX();
		int ghostPosY = ghost->getPosY();
		int ghostWidth = ghost->getSpriteWidth();
		int ghostHeight = ghost->getSpriteWidth();

		SDL_Rect ghostRect = { ghostPosX, ghostPosY, ghostWidth, ghostHeight };
		SDL_Rect resultRect;

		SDL_bool result = SDL_IntersectRect(&pacmanRect, &ghostRect, &resultRect);
		if (result == SDL_TRUE && ghost->getState() == ALIVE) 
		{
			pacman->setCollisionState(true);
			ghostIds.push_back(i);
		}
	}

	return ghostIds;
}

void EntityManager::switchToNormalState(std::vector<BaseEntity*>* entities)
{
	for (auto entity : *entities)
	{
		entity->powerUpOver();
	}
}
