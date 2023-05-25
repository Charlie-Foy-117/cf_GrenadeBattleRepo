#include "Grenade.h"
#include "AssetManager.h"

Grenade::Grenade()
	: PhysicsObject()
	, playerNum(0)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/grenade.png"));
	sprite.setScale(2.0f, 2.0f);

	collisionOffset = sf::Vector2f(10.0f, 10.0f);
	collisionScale = sf::Vector2f(0.8f, 0.8f);
}

void Grenade::SetPlayerNum(int newPlayerNum)
{
	playerNum = newPlayerNum;
}

void Grenade::SetFireVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;
}

int Grenade::GetPlayerNum()
{
	return playerNum;
}

void Grenade::UpdateAcceleration()
{
}
