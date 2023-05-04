#pragma once
#include <SFML/Graphics.hpp>

enum class CollisionType
{
	AABB,
	CIRCLE
};

class SpriteObject
{
public:

	SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	void SetColliding(bool newColliding);
	bool CheckCollision(SpriteObject other);
	sf::Vector2f GetCollisionDepth(SpriteObject other);

	virtual void HandleCollision(SpriteObject& other);
protected:

	sf::Sprite sprite;
	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;
	CollisionType collisionType;

private:

	float GetCircleColliderRadius();
	sf::Vector2f GetCollisionCentre();
	sf::FloatRect GetAABB();
	sf::Vector2f position;
	bool colliding;
};

