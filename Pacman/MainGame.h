#pragma once
#include <string>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Entities\Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "Debug.h"
#include "Gem.h"

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
	bool m_debugMode;
	int ghostNum;
	int m_tileWidth;
	int m_tileHeight;

	std::vector<Ghost> m_ghosts;

	Pacman m_pacman;
	Gem m_gem;
	Gem m_wall;
	Board m_board;
	Debug m_debug;

	SDL_Event m_e;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* m_surface;
};

