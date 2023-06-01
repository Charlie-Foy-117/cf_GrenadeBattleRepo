#pragma once
#include <SFML/System.hpp>

namespace VectorHelper
{
	float SquareMagnitude(sf::Vector2f vec);
	float Magnitude(sf::Vector2f vec);

	sf::Vector2f Normalise(sf::Vector2f vec);

	float DotProduct(sf::Vector3f a, sf::Vector3f b);
	float DotProduct(sf::Vector2f a, sf::Vector2f b);
	sf::Vector3f CrossProduct(sf::Vector3f a, sf::Vector3f b);

	sf::Vector3f GetReflection(sf::Vector3f incident, sf::Vector3f normal);
	sf::Vector2f GetReflection(sf::Vector2f incident, sf::Vector2f normal);

	sf::Vector3f GetNormal(sf::Vector3f line1, sf::Vector3f line2);
	sf::Vector2f GetNormal(sf::Vector2f line1);
}
