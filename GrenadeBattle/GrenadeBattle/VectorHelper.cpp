#include "VectorHelper.h"

float VectorHelper::SquareMagnitude(sf::Vector2f vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float VectorHelper::Magnitude(sf::Vector2f vec)
{
	return sqrt(SquareMagnitude(vec));
}

sf::Vector2f VectorHelper::Normalise(sf::Vector2f vec)
{
	float mag = Magnitude(vec);

	vec.x /= mag;
	vec.y /= mag;

	return vec;
}