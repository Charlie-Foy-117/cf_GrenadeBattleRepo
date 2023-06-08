#include "Easing.h"

sf::Vector2f Easing::EaseOutQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
	//Practical Task - Easing Function
	//
	//

	return -change * time / duration * ((time / duration) - 2) + begin;
}