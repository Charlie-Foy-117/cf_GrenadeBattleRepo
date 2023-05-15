#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
	: SpriteObject()
	, velocity()
	, acceleration()
	, twoFramesOldPosition(100, 300)
{
}

void PhysicsObject::Update(sf::Time frameTime)
{
	
}

void PhysicsObject::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void PhysicsObject::HandleCollision(PhysicsObject& other)
{
}

void PhysicsObject::UpdateAcceleration()
{
}
