#pragma once
#include <SFML/System.hpp>

namespace VectorHelper
{
	float SquareMagnitude(sf::Vector2f vec);
	float Magnitude(sf::Vector2f vec);

	sf::Vector2f Normalise(sf::Vector2f vec);
}
