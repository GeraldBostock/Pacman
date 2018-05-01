#pragma once
#include <SDL.h>

#include "..\Texture.h"
#include "..\Helper\Timer.h"
#include "BaseEntity.h"

class Pacman : public BaseEntity
{
public:
	Pacman();
	~Pacman();

	void loadDeathAnimation(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale);
	void loadPowerUpAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale);
	void loadBlinkAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale);

	void update(int screenWidth, int screenHeight, bool canChangeDirection, bool canMove) override;
	void draw(SDL_Renderer* renderer) override;
	void free() override;

	void die() override;
	void revive();
	void powerUp();
	void powerUpOver() override;
	void blink() override;
	bool isAnimationOver();

private:
	EntityAnimation m_deathAnimation;
	EntityAnimation m_poweredUp;
	EntityAnimation m_blinkAnim;

	EntityAnimation* m_currentAnimation;
	float m_rotationAngle;
};

