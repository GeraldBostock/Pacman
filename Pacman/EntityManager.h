#pragma once
#include <vector>
#include <SDL.h>

#include "Entities\BaseEntity.h"
#include "Entities\Pacman.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	std::vector<int> checkForGhostCollision(std::vector<BaseEntity*>* entities);
	void switchToNormalState(std::vector<BaseEntity*>* entities);
};

