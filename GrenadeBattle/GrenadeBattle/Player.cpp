#include "Player.h"
#include "AssetManager.h"

Player::Player()
	: PhysicsObject()
	, pips()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/player_1.png"));
	sprite.setScale(3.0f, 3.0f);

	collisionScale = sf::Vector2f(2.6f, 3.0f);
	collisionOffset = sf::Vector2f(25, 25);

	//add sprites to my pips
	const int NUM_PIPS = 50;
	for (size_t i = 0; i < NUM_PIPS; ++i)
	{
		pips.push_back(sf::Sprite());
		pips[i].setTexture(AssetManager::RequestTexture("Assets/pip.png"));
	}
}

void Player::Update(sf::Time frameTime)
{
	PhysicsObject::Update(frameTime);
}

void Player::Draw(sf::RenderTarget& target)
{
	PhysicsObject::Draw(target);

	float pipTime = 0;
	float pipTimeStep = 0.1f;
	for (size_t i = 0; i < pips.size(); ++i)
	{
		pips[i].setPosition(GetPipPosition(pipTime, sf::Vector2f(0, 2000), sf::Vector2f(500, -1000), sf::Vector2f(500, 500)));
		pipTime += pipTimeStep;
		target.draw(pips[i]);
	}
}

void Player::HandleCollision(SpriteObject& other)
{
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		//move in x direction
		newPosition.x += depth.x;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		//move in y direction
		newPosition.y += depth.y;
		velocity.y = 0;
		acceleration.y = 0;

	}
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 10000;
	const float GRAVITY = 5000;

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

sf::Vector2f Player::GetPipPosition(float pipTime, sf::Vector2f gravity, sf::Vector2f startVelocity, sf::Vector2f startPosition)
{
	//Practical Task - Gravity Prediction
	//
	//
	sf::Vector2f pipPosition;

	pipPosition = (gravity / 2.0f) * pipTime * pipTime + startVelocity * pipTime + startPosition;

	return pipPosition;
}
