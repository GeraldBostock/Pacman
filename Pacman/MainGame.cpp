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

	m_pacman.init(50, 50, "pacman.png", m_renderer, 4, 0.005f);
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
	}
}

void MainGame::draw()
{
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(m_renderer);

	//Rendering goes here
	m_pacman.draw(m_renderer);

	SDL_RenderPresent(m_renderer);
}
