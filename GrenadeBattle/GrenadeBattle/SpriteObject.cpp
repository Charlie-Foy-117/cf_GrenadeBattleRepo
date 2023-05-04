#include "SpriteObject.h"
#include "VectorHelper.h"

SpriteObject::SpriteObject()
	: sprite()
	, position()
	, collisionOffset(0 ,0)
	, collisionScale(1, 1)
	, collisionType(CollisionType::AABB)
	, colliding(false)
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);

	//Practical Task - Collision Geometry
	//
	//
	bool drawCollier = true;
	if (drawCollier)
	{
		switch (collisionType)
		{
			case CollisionType::AABB:
			{
				sf::RectangleShape rect;
				sf::FloatRect rectBounds = GetAABB();

				rect.setPosition(rectBounds.left, rectBounds.top);
				rect.setSize(sf::Vector2f(rectBounds.width, rectBounds.height));

				sf::Color collisionAABBColour = sf::Color::Green;
				if (colliding)
				{
					collisionAABBColour = sf::Color::Green;
				}
				collisionAABBColour.a = 100;
				rect.setFillColor(collisionAABBColour);

				target.draw(rect);
			}
				break;

			case CollisionType::CIRCLE:
			{
				sf::CircleShape circle;
				sf::Vector2f shapePosition = GetCollisionCentre();
				float circleRadius = GetCircleColliderRadius();

				shapePosition.x -= circleRadius;
				shapePosition.y -= circleRadius;

				circle.setPosition(shapePosition);
				circle.setRadius(circleRadius);

				sf::Color collisionAABBColour = sf::Color::Green;
				if (colliding)
				{
					collisionAABBColour = sf::Color::Green;
				}
				collisionAABBColour.a = 100;
				circle.setFillColor(collisionAABBColour);

				target.draw(circle);
			}
				break;
		}
	}
	

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

void SpriteObject::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

bool SpriteObject::CheckCollision(SpriteObject other)
{
	switch (collisionType)
	{
	case CollisionType::AABB:
	{
		if (other.collisionType == CollisionType::AABB)
		{
			return GetAABB().intersects(other.GetAABB());
		}
		else
		{
			//handles a rectangle colliding with a circle

			sf::Vector2f nearestPointToCircle = other.GetCollisionCentre(); //actual circle centre
			sf::FloatRect thisAABB = GetAABB();

			//clamp the circle centre to min and max aabb
			nearestPointToCircle.x = fmaxf(thisAABB.left, fminf(nearestPointToCircle.x, thisAABB.left + thisAABB.width));
			nearestPointToCircle.y = fmaxf(thisAABB.top, fminf(nearestPointToCircle.y, thisAABB.top + thisAABB.height));

			sf::Vector2f displacement = nearestPointToCircle - other.GetCollisionCentre();
			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = other.GetCircleColliderRadius();

			return squareDistance <= circleRadius * circleRadius;
		}
	}
		break;
	case CollisionType::CIRCLE:
	{
		if (other.collisionType == CollisionType::CIRCLE)
		{
			//get the vector representing the displacement between the two circles
			sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

			//get the magnitude of that vector, which is how far apart the circle centres
			float sqaureDistance = VectorHelper::SquareMagnitude(displacement); //todo

			//compare that to the comvined radii of the two circles
			float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

			return sqaureDistance <= combinedRadii * combinedRadii;
		}
		else
		{
			sf::Vector2f nearestPointToCircle = GetCollisionCentre(); //actual circle centre
			sf::FloatRect otherAABB = other.GetAABB();

			//clamp the circle centre to min and max aabb
			nearestPointToCircle.x = fmaxf(otherAABB.left, fminf(nearestPointToCircle.x, otherAABB.left + otherAABB.width));
			nearestPointToCircle.y = fmaxf(otherAABB.top, fminf(nearestPointToCircle.y, otherAABB.top + otherAABB.height));

			sf::Vector2f displacement = nearestPointToCircle - GetCollisionCentre();
			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = GetCircleColliderRadius();

			return squareDistance <= circleRadius * circleRadius;
		}
	}
		break;
	default:
		break;
	}
	return false;
}

sf::Vector2f SpriteObject::GetCollisionDepth(SpriteObject other)
{
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = other.GetAABB();

	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = other.GetCollisionCentre();

	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width / 2.0f + otherAABB.width / 2.0f;
	minDistance.y = thisAABB.height / 2.0f + otherAABB.height / 2.0f;
	sf::Vector2f actualDistance = otherCentre - thisCentre;

	if (actualDistance.x < 0)
	{
		minDistance.x = -minDistance.x;
	}
	if (actualDistance.y < 0)
	{
		minDistance.y = -minDistance.y;
	}

	return actualDistance - minDistance;
}

void SpriteObject::HandleCollision(SpriteObject& other)
{
	//handled in child classes
}

float SpriteObject::GetCircleColliderRadius()
{
	sf::FloatRect spriteBounds = sprite.getLocalBounds();

	spriteBounds.width = spriteBounds.width * collisionScale.x;
	spriteBounds.height = spriteBounds.height * collisionScale.y;

	if (spriteBounds.width > spriteBounds.height)
	{
		return spriteBounds.width / 2.0f;
	}
	else
	{
		return spriteBounds.height / 2.0f;
	}
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	sf::Vector2f centre = position;
	sf::FloatRect spriteBounds = sprite.getLocalBounds();

	centre.x += spriteBounds.width / 2.0f;
	centre.y += spriteBounds.height / 2.0f;
	centre.x += collisionOffset.x;
	centre.y += collisionOffset.y;

	return centre;
}

sf::FloatRect SpriteObject::GetAABB()
{
	sf::FloatRect spriteBounds = sprite.getLocalBounds();
	sf::Vector2f centre = GetCollisionCentre();

	spriteBounds.width = spriteBounds.width * collisionScale.x;
	spriteBounds.height = spriteBounds.height * collisionScale.y;
	spriteBounds.left = centre.x - spriteBounds.width / 2.0f;
	spriteBounds.top = centre.y - spriteBounds.height / 2.0f;

	return spriteBounds;
}
