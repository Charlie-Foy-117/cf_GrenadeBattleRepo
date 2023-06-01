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

float VectorHelper::DotProduct(sf::Vector3f a, sf::Vector3f b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

float VectorHelper::DotProduct(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

sf::Vector3f VectorHelper::CrossProduct(sf::Vector3f a, sf::Vector3f b)
{
	sf::Vector3f c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;

	return c;
}

sf::Vector3f VectorHelper::GetReflection(sf::Vector3f incident, sf::Vector3f normal)
{
	return incident - 2.0f * normal * (DotProduct(incident, normal));
}

sf::Vector2f VectorHelper::GetReflection(sf::Vector2f incident, sf::Vector2f normal)
{
	return incident - 2.0f * normal * (DotProduct(incident, normal));
}

sf::Vector3f VectorHelper::GetNormal(sf::Vector3f line1, sf::Vector3f line2)
{
	return CrossProduct(line1, line2);
}

sf::Vector2f VectorHelper::GetNormal(sf::Vector2f line1)
{
	return sf::Vector2f(line1.y, -line1.x);
}

