#pragma once
#include <time.h>
#include <stdlib.h>

#include "BaseEntity.h"

class Ghost : public BaseEntity
{
public:
	Ghost();
	~Ghost();

	void initColors(Uint32 r, Uint32 g, Uint32 b);
	void handleInput(SDL_Event e) override;
	void draw(SDL_Renderer* renderer) override;

private:
	Uint32 m_r;
	Uint32 m_g;
	Uint32 m_b;

	int m_timeBetweenDirectionChanges;

	Timer m_directionTimer;
};

