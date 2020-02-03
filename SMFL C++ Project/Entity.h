#pragma once
#include "State.h"

class Entity {
public:
	Entity(sf::Texture& texture);

	void RenderTo(sf::RenderWindow& window);
	void SetPosition(sf::Vector2<float> newPos);

	int getX();
	int getY();
	sf::FloatRect getGlobalBounds() const;

protected:
	sf::Sprite entity;
};

