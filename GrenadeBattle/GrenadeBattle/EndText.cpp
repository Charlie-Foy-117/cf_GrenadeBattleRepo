#include "EndText.h"
#include "AssetManager.h"
#include "Easing.h"

EndText::EndText(sf::RenderWindow* newWindow)
	: text()
	, position()
	, window(newWindow)
	, animatingIn(false)
	, animationClock()
{
	text.setFont(AssetManager::RequestFont("Assets/dogica.ttf"));
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);

	ResetPosition();
}

void EndText::Update(sf::Time frameTime)
{
	if (animatingIn)
	{
		float xPos = window->getSize().x / 2.0f - text.getGlobalBounds().width / 2.0f;
		float yPos = window->getSize().y;
		float finalYPos = window->getSize().y / 2.0f - text.getGlobalBounds().height / 2.0f;

		//set start and end positions
		sf::Vector2f begin(xPos, yPos);
		sf::Vector2f change(0, finalYPos - yPos);

		//set duration of the animation
		float duration = 1.0f;
		float time = animationClock.getElapsedTime().asSeconds();

		sf::Vector2f newPosition = Easing::EaseOutQuad(begin, change, duration, time);

		SetPosition(newPosition);

		if (time >= duration)
		{
			SetPosition(begin + change);
			animatingIn = false;
		}
	}
}

void EndText::Draw(sf::RenderTarget& target)
{
	target.draw(text);
}

void EndText::SetPosition(sf::Vector2f newPosition)
{
	text.setPosition(newPosition);
}

void EndText::StartAnimation()
{
	animatingIn = true;
	animationClock.restart();
}

void EndText::ResetPosition()
{
	//reset position back to starting position
	float xPos = window->getSize().x / 2.0f - text.getGlobalBounds().width;
	float yPos = window->getSize().y;
	SetPosition(sf::Vector2f(xPos, yPos));
}

void EndText::Winner(int playerNum)
{
	//converts score to string to display
	std::string winnerString = "Player ";
	winnerString += std::to_string((int)ceil(playerNum));
	text.setString(winnerString + " wins!");
}
