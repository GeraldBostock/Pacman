#include "MainGame.h"



MainGame::MainGame()
{
	m_title = "Pacman";
	m_windowWidth = 1280;
	m_windowHeight = 780;
}

MainGame::MainGame(std::string title, int width, int height)
{
	m_title = title;
	m_windowWidth = width;
	m_windowHeight = height;
}


MainGame::~MainGame()
{
}

void MainGame::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to initialize SDL. SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Failed to create window. SDL Error: %s", SDL_GetError());
		}
		else
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_renderer == NULL) {
				printf("Failed to create renderer. SDL Error: %s", SDL_GetError());
			}
			else
			{
				//Nearest pixel sampling.
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("Could not initialize SDL_Image. SDL_Image error: %s", IMG_GetError());
				}
				else
				{
					m_surface = SDL_GetWindowSurface(m_window);
					SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0xFF, 0xFF, 0xFF));
				}
			}
		}
	}

	m_fire2.init(30, 30, "fire.png", m_renderer, 4, 0.03f, 0.20f);
	m_ghost.init(60, 30, "ghost.png", m_renderer, 4, 0.03f, 0.25f);
	m_ghost2.init(90, 30, "ghost.png", m_renderer, 4, 0.03f, 0.25f);
	m_ghost3.init(120, 30, "ghost.png", m_renderer, 4, 0.03f, 0.25f);
	m_ghost4.init(150, 30, "ghost.png", m_renderer, 4, 0.03f, 0.25f);
	m_ghost5.init(180, 30, "ghost.png", m_renderer, 4, 0.03f, 0.25f);
	m_ghost6.init(210, 30, "ghost.png", m_renderer, 4, 0.03f, 0.25f);
	m_ghost7.init(240, 30, "ghost.png", m_renderer, 4, 0.03f, 0.25f);
	m_fire.init(270, 30, "fire.png", m_renderer, 4, 0.03f, 0.20f);

	m_ghost2.initColors(255, 0, 0);
	m_ghost3.initColors(0, 255, 0);
	m_ghost4.initColors(0, 0, 255);
	m_ghost5.initColors(150, 150, 0);
	m_ghost6.initColors(0, 150, 0);
	m_ghost7.initColors(50, 100, 150);

	m_pacman.init(50, 400, "pacman.png", m_renderer, 4, 0.005f, 0.20f);

	m_board.init(m_windowWidth, m_windowHeight, m_renderer);
}

void MainGame::run()
{
	m_running = true;

	while (m_running)
	{
		while(SDL_PollEvent(&m_e) != 0)
		{
			if (m_e.type == SDL_QUIT) m_running = false;
			m_pacman.handleInput(m_e);
		}

		draw();

		m_pacman.update(m_windowWidth, m_windowHeight);
		m_board.update(m_pacman.getPosX(), m_pacman.getPosY(), m_pacman.getSpriteWidth(), m_pacman.getSpriteHeight(), m_renderer);
	}
}

void MainGame::draw()
{
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(m_renderer);

	//Rendering goes here
	m_board.draw(m_renderer);
	m_ghost.draw(m_renderer);
	m_ghost2.draw(m_renderer);
	m_ghost3.draw(m_renderer);
	m_ghost4.draw(m_renderer);
	m_ghost5.draw(m_renderer);
	m_ghost6.draw(m_renderer);
	m_ghost7.draw(m_renderer);
	m_fire.draw(m_renderer);
	m_fire2.draw(m_renderer);
	m_pacman.draw(m_renderer);

	SDL_RenderPresent(m_renderer);
}
