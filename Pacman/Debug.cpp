#include "Debug.h"



Debug::Debug()
{
}


Debug::~Debug()
{
}

void Debug::init(SDL_Renderer* renderer, int windowWidth, int windowHeight)
{
	if (TTF_Init() == -1) 
	{ 
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError()); 
	}

	m_blendedRect = createDebugRect(windowWidth, windowHeight, renderer);

	m_font = TTF_OpenFont("Assets/font.ttf", 20);

	m_textColor = { 255, 255, 255 };
	m_posXLabel.loadFromRenderedText("X: ", m_textColor, m_font, renderer);
	m_posYLabel.loadFromRenderedText("Y: ", m_textColor, m_font, renderer);

	m_appleCountLabel.loadFromRenderedText("Apples Left: ", m_textColor, m_font, renderer);

	m_fpsLabel.loadFromRenderedText("FPS: ", m_textColor, m_font, renderer);

	m_fire.init(25, 25);
	m_fire.loadAnim("Assets/fire.png", renderer, 4, 0.08f, 0.2f);
}

void Debug::draw(SDL_Renderer* renderer, int windowWidth, int windowHeight, int posX, int posY, int appleNum, float fps)
{
	SDL_Rect debugPanel = { 0, 0, windowWidth / 4, windowHeight };

	SDL_RenderCopy(renderer, m_blendedRect, NULL, &debugPanel);
	m_posXLabel.draw(50, 50, renderer, NULL, 0.0);
	m_posYLabel.draw(50, 75, renderer, NULL, 0.0);
	m_appleCountLabel.draw(50, 100, renderer, NULL, 0.0);
	m_fpsLabel.draw(50, 125, renderer, NULL, 0);

	m_playerPosX.loadFromRenderedText(std::to_string(posX), m_textColor, m_font, renderer);
	m_playerPosY.loadFromRenderedText(std::to_string(posY), m_textColor, m_font, renderer);
	m_appleCount.loadFromRenderedText(std::to_string(appleNum), m_textColor, m_font, renderer);
	m_fpsValue.loadFromRenderedText(std::to_string(fps), m_textColor, m_font, renderer);

	m_playerPosX.draw(75, 50, renderer, NULL, 0.0);
	m_playerPosY.draw(75, 75, renderer, NULL, 0.0);
	m_appleCount.draw(175, 100, renderer, NULL, 0.0);
	m_fpsValue.draw(115, 125, renderer, NULL, 0.0);

	m_fire.draw(renderer);
}

SDL_Texture* Debug::createDebugRect(int windowWidth, int windowHeight, SDL_Renderer* renderer)
{
	SDL_Surface* rect = NULL;
	SDL_Texture* blendedTex = NULL;

	rect = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0, 0, 0, 0);
	if (rect == NULL)
	{
		printf("%s", SDL_GetError());
	}

	blendedTex = SDL_CreateTextureFromSurface(renderer, rect);
	if (blendedTex == NULL)
	{
		printf("%s", SDL_GetError());
	}

	SDL_SetTextureBlendMode(blendedTex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(blendedTex, 150);

	return blendedTex;
}
