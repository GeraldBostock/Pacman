#pragma once
#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Entities\Pacman.h"
#include "Ghost.h"
#include "Board.h"

class MainGame
{
public:
	MainGame();
	MainGame(std::string title, int width, int height);
	~MainGame();

	void init();
	void run();
	void draw();

private:
	std::string m_title;
	int m_windowWidth;
	int m_windowHeight;
	bool m_running;

	Pacman m_pacman;
	Ghost m_ghost;
	Ghost m_ghost2;
	Ghost m_ghost3;
	Ghost m_ghost4;
	Ghost m_ghost5;
	Ghost m_ghost6;
	Ghost m_ghost7;
	Ghost m_fire;
	Ghost m_fire2;
	Board m_board;

	SDL_Event m_e;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* m_surface;
};

