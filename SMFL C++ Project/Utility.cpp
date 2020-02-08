#include "Utility.h"
#include <random>
std::random_device rd;
std::mt19937 mt(rd());


bool isHovered(sf::Sprite sprite, sf::RenderWindow &window)
{
	sf::IntRect tmpRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	if (tmpRect.contains(sf::Mouse::getPosition(window)))
	{
		return true;
	}

	return false;
}

bool is_pressed(sf::Sprite sprite, sf::RenderWindow& window)
{
	if (isHovered(sprite, window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}
int getNumberInRange(int x, int y)
{
	std::uniform_real_distribution<float> uid(x, y);
	return uid(mt);
}