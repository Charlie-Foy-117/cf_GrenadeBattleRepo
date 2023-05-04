#include <SFML/Graphics.hpp>
#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "AssetManager.h"

int main()
{
	//initialise the random number the generator
	srand(time(NULL));

	//create the game
	Game gameInstance; //default constructor

	//this will not end until the game is over
	gameInstance.RunGameLoop();

	//if we get here, the loop exited, so the game is over

	//clean up assets
	AssetManager::DestroyAllAssets();

	//End the program by returning

	return 0;
}