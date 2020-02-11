#include "Asteroids.h"
#include "Define.h"
#include "Bullet.h"
#include "Utility.h"

class Bullet;
class Player;

Asteroids::Asteroids(sf::Texture& texture, float speed): Entity(texture)
{
	this->speed = speed;
	sprite.setTexture(texture);
	SetPosition(sf::Vector2f(2000.0f, getNumberInRange(150, screen_height - 150)));
}

Asteroids::~Asteroids() = default;

bool Asteroids::IsColliding(Entity& entity) const
{
	if (getGlobalBounds().contains(entity.getX(), entity.getY()))
		return true;
	return false;
}


void Asteroids::Update()
{
	sf::Vector2f movement(0.0f, 0.0f);

	movement.x -= speed;

	if (getX() <= 50.0f)
	{
		SetPosition(sf::Vector2f(2000.0f, screen_height / 2));
	}
	entity.move(movement);
}
