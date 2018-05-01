#pragma once
#include <string>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Entities\Pacman.h"
#include "Entities\Ghost.h"
#include "Board.h"
#include "Debug.h"
#include "Gem.h"
#include "EntityManager.h"
#include "GUI.h"
#include "Helper\FPS.h"

const Uint32 POWER_UP_TIME = 10000;

enum State {
	PLAY_STATE,
	DEATH_STATE,
	POWERED_UP_STATE
};

class MainGame
{
public:
	MainGame();
	MainGame(std::string title, int width, int height, int boardWidth, int boardHeight);
	~MainGame();

	void init();
	void run();
	void update();
	void draw();
	void restart();
	void free();

private:
	std::string m_title;
	int m_windowWidth;
	int m_windowHeight;
	bool m_running;
	bool m_debugMode;
	int m_entityNum;
	int m_tileWidth;
	int m_tileHeight;
	int m_remainingHealth;
	float m_framesPerSecond;

	int m_boardWidth;
	int m_boardHeight;

	std::vector<BaseEntity*> m_entities;

	State m_gameState;

	Pacman* m_pacman;
	Board m_board;
	Debug m_debug;
	EntityManager m_entityManager;
	GUI m_gui;

	SDL_Event m_e;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* m_surface;

	FPS m_fps;

	Timer m_powerUpTimer;
};

