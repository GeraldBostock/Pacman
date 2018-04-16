#pragma once
#include "Entities\BaseEntity.h"

class Ghost : public BaseEntity
{
public:
	Ghost();
	~Ghost();

	void draw(SDL_Renderer* renderer);
	void initColors(Uint32 r, Uint32 g, Uint32 b);

private:
	Uint32 m_r;
	Uint32 m_g;
	Uint32 m_b;
};

