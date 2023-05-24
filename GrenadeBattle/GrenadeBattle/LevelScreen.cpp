#include "LevelScreen.h"
#include <fstream>
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, gameRunning(true)
	, currentLevel(1)
	, platforms()
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		player.Update(frameTime);
		player.SetColliding(false);

		for (size_t i = 0; i < platforms.size(); i++)
		{
			if (player.CheckCollision(*platforms[i]))
			{
				player.SetColliding(true);
				platforms[i]->SetColliding(true);
				player.HandleCollision(*platforms[i]);
				platforms[i]->HandleCollision(player);
			}
		}
	}
	else
	{
		//end screen
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	for (size_t i = 0; i < platforms.size(); i++)
	{
		platforms[i]->Draw(target);
	}
	player.Draw(target);
}

void LevelScreen::Restart()
{
	LoadLevel(currentLevel);
}

bool LevelScreen::LoadLevel(int levelNumber)
{
	//construct level name from number
	std::string levelName = "Level" + std::to_string(levelNumber);

	bool success = LoadLevel(levelName);

	if (success)
	{
		currentLevel = levelNumber;
	}

	return success;
}

bool LevelScreen::LoadLevel(std::string fileName)
{
	//open the level file
	std::ifstream inFile;
	std::string filePath = "Assets/Levels/" + fileName + ".txt";

	inFile.open(filePath);

	//Make sure the file was actually opened
	if (!inFile)
	{
		//file was not opened
		return false;
	}

	//clear out platforms before making new ones
	//make sure to delete BEFORE clearing
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}
	platforms.clear();

	//set the starting x and y cooridnates used to position or level objects
	float x = 0.0f;
	float y = 0.0f;

	//define the spacing we will use for our grid
	const float X_SPACE = 35.0f;
	const float Y_SPACE = 35.0f;

	//read each character one by one from the file
	char ch;
	//each time, try to read the next character
	//if successful, execute the body of loop
	//the "noskipws" means our input from the file will include the white space(spaces and new lines)

	while (inFile >> std::noskipws >> ch)
	{
		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
		else if (ch == 'P')
		{
			player.SetPosition(x, y);
		}
		else if (ch == 'T')
		{
			platforms.push_back(new Platform(sf::Vector2f(x, y)));
		}
		else if (ch == '-')
		{
			//do nothing - empty space
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}
	}

	//close file no that we are done with it
	inFile.close();

	//set out game to start
	gameRunning = true;
	//return true because we successfully loaded the file
	return true;
}
