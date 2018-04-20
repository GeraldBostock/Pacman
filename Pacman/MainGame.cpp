#include "MainGame.h"



MainGame::MainGame()
{
	m_title = "Pacman";
	m_windowWidth = 1280;
	m_windowHeight = 780;
	m_debugMode = false;
	ghostNum = 20;
}

MainGame::MainGame(std::string title, int width, int height)
{
	m_title = title;
	m_windowWidth = width;
	m_windowHeight = height;
	m_debugMode = false;
	ghostNum = 20;
}


MainGame::~MainGame()
{
}

void MainGame::init()
{
	srand(time(NULL));

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
				SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

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

	for (int i = 0; i < ghostNum; i++)
	{
		Ghost ghost;
		int x = 4;
		int y = 4;
		int offsetX = rand() % 30;
		int offsetY = rand() % 18;

		x += offsetX * 40;
		y += offsetY * 40;

		ghost.init(x, y, "ghost2.png", m_renderer, 4, 0.03f, 0.25f);
		ghost.initColors(rand() % 255, rand() % 255, rand() % 255);
		m_ghosts.push_back(ghost);
	}

	m_gem.init(527, 47, "gem.png", m_renderer, 1, 0.0f, 0.20f);
	m_pacman.init(204, 204, "pacman.png", m_renderer, 4, 0.005f, 0.25f);
	m_wall.init(400, 400, "wall.png", m_renderer, 1, 0.0f, 0.25f);

	m_board.init(m_windowWidth, m_windowHeight, m_renderer);
	m_tileWidth = m_board.getTileWidth();
	m_tileHeight = m_board.getTileHeight();

	m_debug.init(m_renderer, m_windowWidth, m_windowHeight);
}

void MainGame::run()
{
	m_running = true;

	while (m_running)
	{

		while(SDL_PollEvent(&m_e) != 0)
		{
			if (m_e.type == SDL_QUIT) m_running = false;
			else if (m_e.type == SDL_KEYUP && m_e.key.keysym.sym == SDLK_QUOTEDBL) m_debugMode = !m_debugMode;
			m_pacman.handleInput(m_e, m_board.canTurn(&m_pacman));
		}

		draw();

		m_board.prepare();

		for (int i = 0; i < ghostNum; i++)
		{
			m_ghosts.at(i).update(m_windowWidth, m_windowHeight, m_board.canTurn(&m_ghosts.at(i)), m_board.isColliding(&m_ghosts.at(i)));
			m_board.updateGhost(&m_ghosts.at(i), m_renderer);
		}

		m_board.updateGhost(&m_gem, m_renderer);
		m_pacman.update(m_windowWidth, m_windowHeight, m_tileWidth, m_tileHeight, m_board.canTurn(&m_pacman), m_board.isColliding(&m_pacman));
		m_board.updatePacman(&m_pacman, m_renderer);
		m_gem.update(SDL_GetTicks());
	}
}

void MainGame::draw()
{
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(m_renderer);

	//Rendering goes here
	m_board.draw(m_renderer, m_debugMode);
	for (int i = 0; i < ghostNum; i++)
	{
		m_ghosts.at(i).draw(m_renderer);
	}
	m_pacman.draw(m_renderer);
	m_gem.draw(m_renderer);
	m_wall.draw(m_renderer);

	if (m_debugMode) m_debug.draw(m_renderer, m_windowWidth, m_windowHeight, m_pacman.getPosX(), m_pacman.getPosY(), m_board.getAppleCount());

	SDL_RenderPresent(m_renderer);
}
