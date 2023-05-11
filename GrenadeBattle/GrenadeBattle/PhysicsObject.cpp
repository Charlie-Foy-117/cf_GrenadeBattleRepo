#include "PhysicsObject.h"

enum class PhysicsType
{
	SYMPLECTIC_EULER,
	VELOCITY_VERLET
};

PhysicsObject::PhysicsObject()
	: SpriteObject()
	, velocity()
	, acceleration()
	, twoFramesOldPosition(100, 300)
{
}

void PhysicsObject::Update(sf::Time frameTime)
{
	//Practical Task - Physics Alternatives
	//
	//
	const float DRAG = 10.0f;
	const PhysicsType physics = PhysicsType::VELOCITY_VERLET;
	sf::Vector2f lastFramePos = GetPosition();
	sf::Vector2f halfFrameVelocity;

	switch (physics)
	{
	case PhysicsType::VELOCITY_VERLET:

		//velocity verlet

		//get the half frame velocity using the previous frame's acceleration
		halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		//get new frame's position using half frame velocity
		SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());

		//update the acceleration
		UpdateAcceleration();

		//get new frame's velocity using half frame velocity and updated acceleration
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		//calculate the drag
		velocity = velocity - velocity * DRAG * frameTime.asSeconds();

		break;
	case PhysicsType::SYMPLECTIC_EULER:

		//semi-implicit / symplectic euler

		//update the velocity to account for acceleration
		velocity = velocity + acceleration * frameTime.asSeconds();

		//calculate the drag
		velocity = velocity - velocity * DRAG * frameTime.asSeconds();

		//set the new position using the calculted velocity
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());

		//update the acceleration
		UpdateAcceleration();

		break;
	default:
		break;

		//two frames ago (for next frame)
		twoFramesOldPosition = lastFramePos;
	}
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
