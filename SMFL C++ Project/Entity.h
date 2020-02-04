#pragma once
#include "State.h"

class Entity {
public:
	Entity(sf::Texture& texture);

	void RenderTo(sf::RenderWindow& window) const;
	void SetPosition(sf::Vector2<float> newPos);

	float getX() const;
	float getY() const;
	sf::FloatRect getGlobalBounds() const;

protected:
	sf::Sprite entity;
};

