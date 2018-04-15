#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile(std::string filePath, SDL_Renderer* renderer, float scale);
	void free();
	void draw(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle);

	int getWidth();
	int getHeight();
	float getScale();

private:
	SDL_Texture* m_texture;
	
	int m_texWidth;
	int m_texHeight;

	float m_scale;
};

