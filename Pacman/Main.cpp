#include <stdio.h>

#include "MainGame.h"

int main(int argc, char** argv)
{
	MainGame mainGame("Pacman", 1540, 760, 1320, 760);
	mainGame.init();
	mainGame.run();

	return 0;
}