#include "Player.h"
#include "AssetManager.h"
#include "VectorHelper.h"
#include "LevelScreen.h"

enum class PhysicsType
{
	SYMPLECTIC_EULER,
	VELOCITY_VERLET
};

Player::Player(LevelScreen* newLevelscreen, int playerNum)
	: PhysicsObject()
	, pips()
	, grenadeVelocity()
	, controllerDeadzone(20.0f)
	, levelScreen(newLevelscreen)
	, cooldownClock()
	, cooldown(0.5f)
	, currentPlayer(playerNum)
	, onGroundTimer()
	, onGroundCooldown(0.1f)
{
	if (currentPlayer == 0)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/player_1_stand.png"));
		sprite.setScale(3.0f, 3.0f);
	}
	else if (currentPlayer == 1)
	{
		sprite.setTexture(AssetManager::RequestTexture("Assets/player_2_stand.png"));
		sprite.setScale(3.0f, 3.0f);
	}

	collisionScale = sf::Vector2f(2.6f, 3.0f);
	collisionOffset = sf::Vector2f(25, 25);

	hasDrag = true;

	//add sprites to my pips
	const int NUM_PIPS = 10;
	for (size_t i = 0; i < NUM_PIPS; ++i)
	{
		pips.push_back(sf::Sprite());
		pips[i].setTexture(AssetManager::RequestTexture("Assets/pip.png"));
	}
}

void Player::Update(sf::Time frameTime)
{
	PhysicsObject::Update(frameTime);

	UpdatePipAngle();

	if (cooldownClock.getElapsedTime().asSeconds() > cooldown)
	{
		if (sf::Joystick::isButtonPressed(currentPlayer, 2))
		{
			levelScreen->FireGrenade(sf::Vector2f(GetPosition().x + 25.0f, GetPosition().y + 25.0f), grenadeVelocity, currentPlayer);
			cooldownClock.restart();
		}
	}
	
	
}

void Player::Draw(sf::RenderTarget& target)
{
	PhysicsObject::Draw(target);

	float pipTime = 0;
	float pipTimeStep = 0.1f;
	for (size_t i = 0; i < pips.size(); ++i)
	{
		pips[i].setPosition(GetPipPosition(pipTime, sf::Vector2f(0, 5000), grenadeVelocity, sf::Vector2f(GetPosition().x + 25.0f, GetPosition().y + 25.0f)));
		pipTime += pipTimeStep;
		target.draw(pips[i]);
	}
}

void Player::HandleCollision(PhysicsObject& other)
{
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		//move in x direction
		newPosition.x += depth.x * 2.0f;
		velocity.x = 0;
	}
	else
	{
		//move in y direction
		newPosition.y += depth.y;

		if (depth.y < 0)
		{
			onGroundTimer.restart();

			if (velocity.y > 0)
				velocity.y = 0;
		}
	}
	SetPosition(newPosition);
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 10000;
	const float GRAVITY = 5000;
	const float JUMPSPEED = 1500;

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::isButtonPressed(currentPlayer, 0))
	{
		if (onGroundTimer.getElapsedTime().asSeconds() <= onGroundCooldown)
		{
			velocity.y = -JUMPSPEED;
		}
	}
	else
	{
		acceleration.y = GRAVITY;
	}


	if (sf::Joystick::isConnected(0))
	{
		float axisX = sf::Joystick::getAxisPosition(currentPlayer, sf::Joystick::X);

		if (abs(axisX) > controllerDeadzone)
		{
			if (axisX > 0)
			{
				acceleration.x = ACCEL;
			}
			if (axisX < 0)
			{
				acceleration.x = -ACCEL;
			}
		}
	}
}

sf::Vector2f Player::GetPipPosition(float pipTime, sf::Vector2f gravity, sf::Vector2f startVelocity, sf::Vector2f startPosition)
{
	//Practical Task - Gravity Prediction
	//
	//
	sf::Vector2f pipPosition;

	pipPosition = (gravity / 2.0f) * pipTime * pipTime + startVelocity * pipTime + startPosition;

	return pipPosition;
}

void Player::SetGrenadeVelocity(float xVel, float yVel)
{
	grenadeVelocity = sf::Vector2f(xVel, yVel);
}

void Player::UpdatePipAngle()
{
	if (sf::Joystick::isConnected(0))
	{
		float speed = 15.0f;
		float axisU = sf::Joystick::getAxisPosition(currentPlayer, sf::Joystick::U);
		float axisV = sf::Joystick::getAxisPosition(currentPlayer, sf::Joystick::V);

		sf::Vector2f direction = sf::Vector2f(axisU, axisV);

		if (abs(axisU) > controllerDeadzone || abs(axisV) > controllerDeadzone)
		{
			VectorHelper::Normalise(direction);
			sf::Vector2f newVelocity = speed * direction;
			SetGrenadeVelocity(newVelocity.x, newVelocity.y);
		}
	}
}
