#include "Player.h"

enum class PhysicsType
{
	FORWARD_EULER,
	BACKWARD_EULER,
	SYMPLECTIC_EULER,
	POSITION_VERLET,
	VELOCITY_VERLET
};

Player::Player()
	:SpriteObject()
	, twoFramesOldPosition()
	, velocity()
	, acceleration()
{
}

void Player::Update(sf::Time frameTime)
{

	//Practical Task - Physics Alternatives
	//
	//
	const float DRAG = 10.0f;
	const PhysicsType physics = PhysicsType::POSITION_VERLET;
	sf::Vector2f lastFramePos = GetPosition();

	switch (physics)
	{
	case PhysicsType::VELOCITY_VERLET:
		
		//velocity verlet
		 
		//get the half frame velocity using the previous frame's acceleration
		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

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

void Player::UpdateAcceleration()
{
	const float ACCEL = 10000;
	const float GRAVITY = 1000;

	//Update acceleration
	acceleration.x = 0;
	acceleration.y = GRAVITY;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		acceleration.y = -ACCEL;
	}
	else
	{
		acceleration.y = GRAVITY;
	}
}
