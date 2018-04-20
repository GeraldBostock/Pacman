#pragma once
#include "Entities\BaseEntity.h"

class Gem : public BaseEntity
{
public:
	Gem();
	~Gem();

	void update(Uint32 ticks);

private:
	int y = 0;
};

