#include "LifeCounter.h"
#include "AssetManager.h"
#include "Player.h"

LifeCounter::LifeCounter(Player* newPlayer, sf::Vector2f newPosition)
	: player(newPlayer)
	, lifeCounter()
{
	lifeCounter.setFont(AssetManager::RequestFont("Assets/dogica.ttf"));
	lifeCounter.setCharacterSize(50);
	lifeCounter.setFillColor(sf::Color::White);

	SetPosition(newPosition);
}

void LifeCounter::Draw(sf::RenderTarget& target)
{
	SetLifeValue(player->GetLives());
	target.draw(lifeCounter);
}

void LifeCounter::SetPosition(sf::Vector2f newPosition)
{
	lifeCounter.setPosition(newPosition);
}

void LifeCounter::SetLifeValue(int numOfLives)
{
	//converts lives to string to display
	std::string liveValue;
	liveValue += std::to_string((int)ceil(numOfLives));
	lifeCounter.setString(liveValue);
}
