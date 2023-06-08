#pragma once
#include <SFML/Graphics.hpp>

namespace Easing {

	sf::Vector2f EaseOutQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time);
}