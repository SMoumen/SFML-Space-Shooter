#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Bullet :
	public Entity
{
public :
	Bullet(sf::Texture& texture, sf::Vector2<float> vect);
	void Update(bool isBulletFiring, int bulletSpeed, int playerX, int playerY, bool marked);
	bool marked = false;
};
