#pragma once
#include <time.h>
#include <stdlib.h>

#include "BaseEntity.h"

class Ghost : public BaseEntity
{
public:
	Ghost();
	~Ghost();

	void initColors(Uint32 r, Uint32 g, Uint32 b);
	void handleInput(SDL_Event e) override;
	void draw(SDL_Renderer* renderer) override;

	void loadScaredAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale);
	void loadDeadAnim(std::string texturePath, SDL_Renderer* renderer, int animFrames, float timeBetweenFrames, float scale);

	void fear() override;
	void die() override;
	void powerUpOver() override;

	EntityState getState() override;

private:
	EntityAnimation m_scaredAnim;
	EntityAnimation m_deadAnim;

	EntityAnimation* m_currentAnim;

	Uint32 m_r;
	Uint32 m_g;
	Uint32 m_b;

	int m_timeBetweenDirectionChanges;

	Timer m_directionTimer;

	EntityState m_currentState;
};

