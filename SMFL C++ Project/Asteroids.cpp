#include "Asteroids.h"
#include "Define.h"
#include "Bullet.h"
#include "math.h"
#include "Utility.h"
#define _USE_MATH_DEFINES

class Bullet;
class Player;

Asteroids::Asteroids(sf::Texture& texture,float speed): Entity(texture)
{
	this->speed = speed;
	sprite.setTexture(texture);
	SetPosition(sf::Vector2f(2000.0f, getNumberInRange(150, screen_height - 150)));
	//entity.setOrigin(entity.getGlobalBounds().width / 2, entity.getGlobalBounds().height / 2);
	
}

Asteroids::~Asteroids() = default;
bool Asteroids::Colliding(Entity& entity) 
{
	if (getGlobalBounds().contains(entity.getX(), entity.getY()))
		return true;
	return false;
	
}


void Asteroids::Update() 
{
	count++;
	sf::Vector2f movement(0.0f, 0.0f);
	if (life == true)
	{
		movement.x -= speed;
		
		if (getX() <= 50.0f)
		{
			SetPosition(sf::Vector2f(2000.0f, screen_height / 2));
		}
		entity.move(movement);

	}

}

/*void Asteroids::RenderTo(sf::RenderWindow& window) const
{
	window.draw(sprite);
}*/
