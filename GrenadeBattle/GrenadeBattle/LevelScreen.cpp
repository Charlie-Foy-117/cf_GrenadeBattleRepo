#include "LevelScreen.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, gameRunning(true)
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		player.Update(frameTime);
		player.SetColliding(false);
	}
	else
	{
		//end screen
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	player.Draw(target);
}

void LevelScreen::Restart()
{
	player.SetPosition(600, 600);
}
