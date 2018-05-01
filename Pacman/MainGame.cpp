#include "MainGame.h"



MainGame::MainGame()
{
	m_title = "Pacman";
	m_windowWidth = 1280;
	m_windowHeight = 780;
	m_debugMode = false;
	m_entityNum = 20;
}

MainGame::MainGame(std::string title, int width, int height, int boardWidth, int boardHeight)
{
	m_title = title;
	m_windowWidth = width;
	m_windowHeight = height;
	m_debugMode = false;
	m_entityNum = 20;
	m_gameState = PLAY_STATE;
	m_boardWidth = boardWidth;
	m_boardHeight = boardHeight;
	m_remainingHealth = 3;
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

	//m_board.init(m_windowWidth, m_windowHeight, m_renderer);
	m_board.initFromFile("Assets/map.pac", m_renderer);
	m_tileWidth = m_board.getTileWidth();
	m_tileHeight = m_board.getTileHeight();

	m_pacman = new Pacman();

	Position pacmanPos = m_board.getPacmanStartPos();

	m_pacman->init(pacmanPos.x, pacmanPos.y);
	m_pacman->loadAnim("Assets/Pacman/pacman.png", m_renderer, 4, 0.05f, 0.25f);
	m_pacman->loadDeathAnimation("Assets/Pacman/pacmanDeath.png", m_renderer, 8, 0.09f, 0.25f);
	m_pacman->loadPowerUpAnim("Assets/Pacman/poweredUp.png", m_renderer, 4, 0.05f, 0.25f);
	m_pacman->loadBlinkAnim("Assets/Pacman/blink.png", m_renderer, 4, 0.05f, 0.25f);
	m_entities.push_back(m_pacman);

	std::vector<Position>* ghosts = m_board.getGhostsStartPos();

	for (int i = 0; i < ghosts->size(); i++)
	{
		Position ghostPos = ghosts->at(i);
		Ghost *ghost;
		ghost = new Ghost();

		ghost->init(ghostPos.x, ghostPos.y);
		ghost->loadAnim("Assets/ghost.png", m_renderer, 4, 0.1f, 0.25f);
		ghost->loadScaredAnim("Assets/scared.png", m_renderer, 4, 0.1f, 0.25f);
		ghost->loadDeadAnim("Assets/deadGhost.png", m_renderer, 4, 0.1f, 0.25f);
		ghost->initColors(rand() % 255, rand() % 255, rand() % 255);
		m_entities.push_back(ghost);
	}

	m_entityNum = ghosts->size() + 1;

	m_debug.init(m_renderer, m_windowWidth, m_windowHeight);

	m_gui.loadMedia(m_renderer);
	m_fps.init();
}

void MainGame::run()
{
	m_running = true;

	while (m_running)
	{
		m_framesPerSecond = m_fps.think();

		while(SDL_PollEvent(&m_e) != 0)
		{
			if (m_e.type == SDL_QUIT) m_running = false;
			else if (m_e.type == SDL_KEYUP && m_e.key.keysym.sym == SDLK_QUOTEDBL) m_debugMode = !m_debugMode;

			if(m_gameState != DEATH_STATE)
				m_entities.at(0)->handleInput(m_e);
		}

		if (m_gameState == POWERED_UP_STATE)
		{
			Uint32 elapsedTime = m_powerUpTimer.getTicks();
			if (elapsedTime >= POWER_UP_TIME)
			{
				m_gameState = PLAY_STATE;
				m_entityManager.switchToNormalState(&m_entities);
			}
			else if(POWER_UP_TIME - elapsedTime < 3000)
			{
				m_pacman->blink();
			}
		}


		if (m_gameState != DEATH_STATE)
		{
			for (int i = 1; i < m_entityNum; i++) m_entities.at(i)->handleInput(m_e);
			update();
		}

		std::vector<int> ghostIds = m_entityManager.checkForGhostCollision(&m_entities);
		if (ghostIds.size() != 0 && m_gameState != DEATH_STATE)
		{
			if (m_gameState == POWERED_UP_STATE)
			{
				for (auto ghostId : ghostIds)
				{
					m_entities.at(ghostId)->die();
				}
			}
			else if (m_gameState == PLAY_STATE)
			{
				m_pacman->die();
				m_gameState = DEATH_STATE;
			}
		}

		draw();

		if (m_gameState == DEATH_STATE && m_pacman->isAnimationOver())
		{
			restart();
			m_remainingHealth--;
		}
	}

	free();
}

void MainGame::update()
{
	m_board.prepare();

	for (int i = 0; i < m_entityNum; i++)
	{
		m_entities.at(i)->update(m_boardWidth, m_boardHeight, m_board.canTurn(m_entities.at(i)), m_board.canMove(m_entities.at(i), m_boardWidth, m_boardHeight));
		if (i == 0)
		{
			if (m_board.updatePacman(m_entities.at(i)))
			{
				m_gameState = POWERED_UP_STATE;
				m_powerUpTimer.start();
				m_pacman->powerUp();
				for (int j = 1; j < m_entityNum; j++)
				{
					if(m_entities.at(j)->getState() == ALIVE)
						m_entities.at(j)->fear();
				}
			}
		}
		else m_board.updateGhost(m_entities.at(i));
	}
}

void MainGame::draw()
{
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(m_renderer);

	//Rendering goes here
	m_board.draw(m_renderer, m_debugMode);

	for (int i = 0; i < m_entityNum; i++)
	{
		m_entities.at(i)->draw(m_renderer);
	}

	if (m_debugMode) m_debug.draw(m_renderer, m_boardWidth, m_boardHeight, m_pacman->getPosX(), m_pacman->getPosY(), m_board.getAppleCount(), m_framesPerSecond);
	m_gui.draw(m_remainingHealth, m_renderer);

	SDL_RenderPresent(m_renderer);
}

void MainGame::restart()
{
	Position pacmanPos = m_board.getPacmanStartPos();

	m_pacman->setPosX(pacmanPos.x);
	m_pacman->setPosY(pacmanPos.y);

	std::vector<Position>* ghosts = m_board.getGhostsStartPos();

	for (int i = 1; i < m_entities.size(); i++)
	{
		Position ghostPos = ghosts->at(i - 1);
		BaseEntity* ghost = m_entities.at(i);
		ghost->setPosX(ghostPos.x);
		ghost->setPosY(ghostPos.y);
		
	}

	m_entityNum = ghosts->size() + 1;

	m_gameState = PLAY_STATE;
	m_pacman->revive();
}

void MainGame::free()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities.at(i)->free();
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	IMG_Quit();
	SDL_Quit();
}
