#pragma once
#include <SFML/Graphics.hpp>

class SpriteObject
{
public:

	SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	float GetHeight();
	float GetWidth();
protected:

	sf::Sprite sprite;
	sf::Vector2f position;
};

