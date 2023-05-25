#include "Platform.h"
#include "AssetManager.h"

Platform::Platform(sf::Vector2f newPosition)
	: PhysicsObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/tile.png"));
	sprite.setScale(2.0f, 2.0f);
	collisionScale = sf::Vector2f(2.0f, 2.0f);
	collisionOffset = sf::Vector2f(10, 10);

	SetPosition(newPosition);
}
