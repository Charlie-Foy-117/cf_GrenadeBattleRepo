#include "Grenade.h"
#include "AssetManager.h"
#include "VectorHelper.h"

Grenade::Grenade()
	: PhysicsObject()
	, playerNum(0)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/grenade.png"));
	sprite.setScale(2.0f, 2.0f);

	collisionOffset = sf::Vector2f(10.0f, 10.0f);
	collisionScale = sf::Vector2f(0.8f, 0.8f);
}

void Grenade::Update(sf::Time frameTime)
{
	PhysicsObject::Update(frameTime);
}

void Grenade::SetPlayerNum(int newPlayerNum)
{
	playerNum = newPlayerNum;
}

void Grenade::SetFireVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;
}

void Grenade::HandleCollision(PhysicsObject& other)
{
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();
	sf::Vector2f otherLine1;
	sf::Vector2f otherLine2;

	if (abs(depth.x) < abs(depth.y))
	{
		//move in x direction
		newPosition.x += depth.x;
		
		otherLine1 = sf::Vector2f(other.GetPosition());
		otherLine2 = sf::Vector2f(other.GetPosition().x, other.GetPosition().y + other.GetHeight());
	}
	else
	{
		//move in y direction
		newPosition.y += depth.y;

		otherLine1 = sf::Vector2f(other.GetPosition());
		otherLine2 = sf::Vector2f(other.GetPosition().x + GetWidth(), other.GetPosition().y);

	}

	sf::Vector2f otherPlane = otherLine2 - otherLine1;
	sf::Vector2f otherNormal = VectorHelper::GetNormal(otherPlane);
	otherNormal = VectorHelper::Normalise(otherNormal);

	sf::Vector2f reflection = VectorHelper::GetReflection(velocity, otherNormal);

	SetPosition(newPosition);
	SetFireVelocity(reflection);
}

int Grenade::GetPlayerNum()
{
	return playerNum;
}

void Grenade::UpdateAcceleration()
{
	const float GRAVITY = 5000;

	acceleration.y = GRAVITY;
}
