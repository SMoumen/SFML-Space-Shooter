#include "Utility.h"
#include <random>
std::random_device rd;
std::mt19937 mt(rd());


bool isHovered(sf::Sprite sprite, sf::RenderWindow &window)
{
	sf::Rect tmpRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width -100, sprite.getGlobalBounds().height -100);
	if (tmpRect.contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		//tmpRect.contains(window.mapPixelToCoords(sf::Vector2<int>(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))))
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