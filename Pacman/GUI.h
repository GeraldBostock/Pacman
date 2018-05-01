#pragma once
#include "Texture.h"

struct HeartContainer {
	int posX;
	int posY;
};

class GUI
{
public:
	GUI();
	~GUI();

	void loadMedia(SDL_Renderer* renderer);
	void draw(int heartNum, SDL_Renderer* renderer);

private:
	Texture m_heartTexture;
	HeartContainer container;
};

