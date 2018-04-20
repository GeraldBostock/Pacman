#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile(std::string filePath, SDL_Renderer* renderer, float scale);
	void loadFromRenderedText(std::string text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
	void free();
	void draw(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle);
	void setColor(Uint32 r, Uint32 g, Uint32 b);

	int getWidth();
	int getHeight();
	float getScale();

	int getOrigWidth();
	int getOrigHeight();

private:
	SDL_Texture* m_texture;
	
	int m_texWidth;
	int m_texHeight;

	int m_originalWidth;
	int m_originalHeight;

	float m_scale;
};

