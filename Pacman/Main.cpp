#include <stdio.h>

#include "MainGame.h"

int main(int argc, char** argv)
{
	MainGame mainGame("Pacman", 1280, 720);
	mainGame.init();
	mainGame.run();

	return 0;
}