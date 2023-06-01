#include "SpriteObject.h"
#include "VectorHelper.h"

SpriteObject::SpriteObject()
	: sprite()
	, position()
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);
}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

void SpriteObject::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

void SpriteObject::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

float SpriteObject::GetHeight()
{
	return sprite.getLocalBounds().height;
}

float SpriteObject::GetWidth()
{
	return sprite.getLocalBounds().width;
}
