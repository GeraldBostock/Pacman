#include "GUI.h"



GUI::GUI()
{
	container = { 1350, 50 };
}


GUI::~GUI()
{
}

void GUI::loadMedia(SDL_Renderer* renderer)
{
	m_heartTexture.loadFromFile("Assets/hearth.png", renderer, 2.0f);
}

void GUI::draw(int heartNum, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect rect = { 1320, 0, 1540 - 1320, 760 };
	SDL_RenderFillRect(renderer, &rect);

	for (int i = 0; i < heartNum; i++)
	{
		int posX = container.posX + i * (m_heartTexture.getWidth() + 5);
		m_heartTexture.draw(posX, container.posY, renderer, NULL, 0);
	}
}
