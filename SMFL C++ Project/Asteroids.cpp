#include "Asteroids.h"
#include "Define.h"
#include "Bullet.h"
#include "Utility.h"

class Bullet;
class Player;

Asteroids::Asteroids(sf::Texture& texture, float speed, float x): Entity(texture)
{
	this->speed = speed;
	sprite.setTexture(texture);
	SetPosition(sf::Vector2f(2000.0f, getNumberInRange(150, screen_height - 150)));
	sprite.setScale(x, x);
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
		SetPosition(sf::Vector2f(getNumberInRange(2000, 20000), getNumberInRange(50, screen_height - 150)));
	}
	entity.move(movement);
}
