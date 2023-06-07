#include "Grenade.h"
#include "AssetManager.h"
#include "VectorHelper.h"
#include "PhysicsObject.h"

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
	//Practical Task - Reflection
	//
	//

	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();
	sf::FloatRect otherAABB = other.GetAABB();
	sf::Vector2f otherPlane;
	sf::Vector2f otherLine1;
	sf::Vector2f otherLine2;

	if (abs(depth.x) < abs(depth.y))
	{
		//move in x direction
		newPosition.x += depth.x;
		
		otherLine1 = sf::Vector2f(otherAABB.left, otherAABB.top);
		otherLine2 = sf::Vector2f(otherAABB.left, otherAABB.top + other.GetHeight());
		otherPlane = otherLine1 - otherLine2;
	}
	else
	{
		//move in y direction
		newPosition.y += depth.y;

		otherLine1 = sf::Vector2f(otherAABB.left, otherAABB.top);
		otherLine2 = sf::Vector2f(otherAABB.left + other.GetWidth(), otherAABB.top);
		otherPlane = otherLine1 - otherLine2;

	}

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
