#include "Utility.h"

bool isHovered(sf::Sprite sprite, sf::RenderWindow &window)
{
	sf::IntRect tmpRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	if (tmpRect.contains(sf::Mouse::getPosition(window)))
	{
		return true;
	}

	return false;
}

bool isPressed(sf::Sprite sprite, sf::RenderWindow& window)
{
	if (isHovered(sprite, window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}
