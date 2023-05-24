#include "Platform.h"
#include "AssetManager.h"

Platform::Platform(sf::Vector2f newPosition)
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/tile.png"));
	sprite.setScale(2.0f, 2.0f);
	collisionScale = sf::Vector2f(2.0f, 2.0f);
	collisionOffset = sf::Vector2f(9, 9);

	SetPosition(newPosition);
}
