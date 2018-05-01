#pragma once
#include <SDL.h>

#define FRAME_VALUES 10

class FPS
{
public:
	FPS();
	~FPS();

	void init();
	float think();

private:

	Uint32 frametimes[FRAME_VALUES];
	Uint32 frametimelast;
	Uint32 framecount;
	float framespersecond;
};

