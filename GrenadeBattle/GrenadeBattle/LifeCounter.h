#pragma once
#include <SFML/Graphics.hpp>

class Player;

class LifeCounter
{
public:

	LifeCounter(Player* newPlayer, sf::Vector2f newPosition);

	void Draw(sf::RenderTarget& target);
	void SetPosition(sf::Vector2f newPosition);
	void SetLifeValue(int numOfLives);

private:

	int playerNum;
	Player* player;
	sf::Text lifeCounter;
};

