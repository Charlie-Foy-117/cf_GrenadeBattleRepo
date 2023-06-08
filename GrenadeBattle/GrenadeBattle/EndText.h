#pragma once
#include <SFML/Graphics.hpp>

class EndText
{
public:

	EndText(sf::RenderWindow* newWindow);

	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

	void SetPosition(sf::Vector2f newPosition);

	void StartAnimation();
	void ResetPosition();
	void Winner(int playerNum);

private:

	sf::Text text;
	sf::Vector2f position;
	sf::RenderWindow* window;

	bool animatingIn;
	sf::Clock animationClock;
};

