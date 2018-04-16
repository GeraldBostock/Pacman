#include "Texture.h"



Texture::Texture()
{
	m_texture = NULL;
	m_texWidth = 0;
	m_texHeight = 0;
}


Texture::~Texture()
{
}

bool Texture::loadFromFile(std::string filePath, SDL_Renderer* renderer, float scale)
{
	free();

	m_scale = scale;

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());

	if (loadedSurface == NULL)
	{
		printf("Failed to load the image to surface. SDL Error: %s", IMG_GetError());
	}
	else
	{
		//Makes the pixels with the given color transparent
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Failed to create texture from surface. SDL Error: %s", SDL_GetError());
		}
		else
		{
			m_texWidth = loadedSurface->w * m_scale;
			m_texHeight = loadedSurface->h * m_scale;
		}

		SDL_FreeSurface(loadedSurface);
		m_texture = newTexture;
	}

	return !m_texture == NULL;
}

void Texture::draw(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle)
{
	SDL_Rect renderQuad = { x, y, m_texWidth, m_texHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w * m_scale;
		renderQuad.h = clip->h * m_scale;
	}

	SDL_RenderCopyEx(renderer, m_texture, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE);
}

void Texture::free()
{
	if (!m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_texWidth = 0;
		m_texHeight = 0;
	}
}

void Texture::setColor(Uint32 r, Uint32 g, Uint32 b)
{
	SDL_SetTextureColorMod(m_texture, r, g, b);
}

int Texture::getWidth()
{
	return m_texWidth;
}

int Texture::getHeight()
{
	return m_texHeight;
}

float Texture::getScale()
{
	return m_scale;
}