#pragma once
#include <time.h>
#include <stdlib.h>

#include "Entities\BaseEntity.h"

class Ghost : public BaseEntity
{
public:
	Ghost();
	~Ghost();

	void draw(SDL_Renderer* renderer);
	void initColors(Uint32 r, Uint32 g, Uint32 b);
	void update(int screenWidth, int screenHeight, bool canMove, bool willCollide);

private:
	Uint32 m_r;
	Uint32 m_g;
	Uint32 m_b;

	int m_timeBetweenDirectionChanges;

	Timer m_directionTimer;
};

