#pragma once
#include <SDL_ttf.h>
#include <stdio.h>

#include "Ghost.h"
#include "Texture.h"

class Debug
{
public:
	Debug();
	~Debug();

	void init(SDL_Renderer* renderer, int windowWidth, int windowHeight);
	void draw(SDL_Renderer* renderer, int windowWidth, int windowHeight, int posX, int posY, int appleNum);

private:
	Texture m_posXLabel;
	Texture m_playerPosX;

	Texture m_posYLabel;
	Texture m_playerPosY;

	Texture m_appleCountLabel;
	Texture m_appleCount;

	SDL_Texture* m_blendedRect;
	SDL_Color m_textColor;
	TTF_Font* m_font;

	Ghost m_fire;

	SDL_Texture* createDebugRect(int windowWidth, int windowHeight, SDL_Renderer* renderer);
};

