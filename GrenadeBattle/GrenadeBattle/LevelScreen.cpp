#include "LevelScreen.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, platform()
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

		if (player.CheckCollision(platform))
		{
			player.SetColliding(true);
			platform.SetColliding(true);
			player.HandleCollision(platform);
			platform.HandleCollision(player);
		}
	}
	else
	{
		//end screen
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	platform.Draw(target);
	player.Draw(target);
}

void LevelScreen::Restart()
{
	player.SetPosition(600, 600);
	platform.SetPosition(600, 900);
}
