#include "LevelScreen.h"
#include "Game.h"
#include <fstream>
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, players()
	, gameRunning(true)
	, currentLevel(1)
	, platforms()
	, grenades()
	, lifeCounters()
	, endText(newGamePointer->GetWindow())
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		if (players[0]->GetAlive() != true || players[1]->GetAlive() != true)
		{
			TriggerEndState();
			gameRunning = false;
		}
		else
		{

			for (size_t i = 0; i < players.size(); i++)
			{
				players[i]->Update(frameTime);
				players[i]->SetColliding(false);
			}

			for (size_t i = 0; i < grenades.size(); i++)
			{
				grenades[i]->Update(frameTime);
				grenades[i]->SetColliding(false);
			}

			for (size_t i = 0; i < players.size(); i++)
			{
				for (size_t j = 0; j < platforms.size(); j++)
				{
					if (players[i]->CheckCollision(*platforms[j]))
					{
						players[i]->SetColliding(true);
						platforms[j]->SetColliding(true);
						players[i]->HandleCollision(*platforms[j]);
						platforms[j]->HandleCollision(*players[i]);
					}
				}
			}

			for (size_t i = 0; i < players.size(); i++)
			{
				for (size_t j = 0; j < grenades.size(); j++)
				{
					if (players[i]->GetCurrentPlayer() != grenades[j]->GetPlayerNum())
					{
						if (players[i]->CheckCollision(*grenades[j]))
						{
							players[i]->SetColliding(true);
							grenades[j]->SetColliding(true);
							players[i]->HandleCollision(*grenades[j]);
							grenades[j]->HandleCollision(*players[i]);
						}
					}
				}
			}

			for (size_t i = 0; i < grenades.size(); i++)
			{
				for (size_t j = 0; j < platforms.size(); j++)
				{
					if (grenades[i]->CheckCollision(*platforms[j]))
					{
						grenades[i]->SetColliding(true);
						platforms[j]->SetColliding(true);
						grenades[i]->HandleCollision(*platforms[j]);
						platforms[j]->HandleCollision(*grenades[i]);
					}
				}
			}
		}
	}
	else
	{
		endText.Update(frameTime);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	for (size_t i = 0; i < platforms.size(); i++)
	{
		platforms[i]->Draw(target);
	}
	for (size_t i = grenades.size(); i > 0; i--)
	{
		if (grenades[i - 1] != nullptr)
		{
			//checks to see if grenades is dead 
			if (grenades[i - 1]->GetAlive() == false)
			{
				//clears grenades memory and deletes it from vector
				delete grenades[i - 1];
				grenades[i - 1] = nullptr;
				grenades.erase(grenades.begin() + (i - 1));
			}
			else
			{
				//draws grenades
				grenades[i - 1]->Draw(target);
			}
		}
	}
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->Draw(target);
	}
	for (size_t i = 0; i < lifeCounters.size(); i++)
	{
		lifeCounters[i]->Draw(target);
	}

	//if game is not running draw endText
	if (!gameRunning)
	{
		endText.Draw(target);
	}
}

void LevelScreen::FireGrenade(sf::Vector2f position, sf::Vector2f fireVelocity, int playerNum)
{
	grenades.push_back(new Grenade(playerNum));
	grenades.back()->SetPlayerNum(playerNum);
	grenades.back()->SetPosition(position);
	grenades.back()->SetFireVelocity(fireVelocity);
}

void LevelScreen::TriggerEndState()
{
	int winner = 0;
	if (players[0]->GetAlive() && !players[1]->GetAlive())
	{
		winner = 1;
	}
	else if (players[1]->GetAlive() && !players[0]->GetAlive())
	{
		winner = 2;
	}
	else
	{
		//error...
	}

	//plays win state depending on the players alive status
	endText.Winner(winner);
	endText.StartAnimation();
}

void LevelScreen::Restart()
{
	for (size_t i = 0; i < grenades.size(); i++)
	{
		delete grenades[i];
		grenades[i] = nullptr;
	}
	for (size_t i = 0; i < lifeCounters.size(); i++)
	{
		delete lifeCounters[i];
		lifeCounters[i] = nullptr;
	}
	for (size_t i = 0; i < players.size(); i++)
	{
		delete players[i];
		players[i] = nullptr;
	}

	players.push_back(new Player(this, 0));
	players.push_back(new Player(this, 1));

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
	const float X_SPACE = 50.0f;
	const float Y_SPACE = 50.0f;

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
			for (size_t i = 0; i < players.size(); i++)
			{
				players[i]->SetPosition(x, y);
			}
		}
		else if (ch == 'T')
		{
			platforms.push_back(new Platform(sf::Vector2f(x, y)));
		}
		else if (ch == '1')
		{
			lifeCounters.push_back(new LifeCounter(players[0], sf::Vector2f(x, y)));
		}
		else if (ch == '2')
		{
			lifeCounters.push_back(new LifeCounter(players[1], sf::Vector2f(x, y)));
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
