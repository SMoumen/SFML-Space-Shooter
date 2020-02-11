#include "Bullet.h"
#include "Define.h"

Bullet::Bullet(sf::Texture& texture) : Entity(texture)
{
	entity.setOrigin(float(texture.getSize().x / 2), texture.getSize().y / 2);
}


void Bullet::Update(bool isBulletFiring, int bulletSpeed, int playerX, int playerY)
{
	if (getX() > screen_width)
	{
		SetPosition(sf::Vector2f(5000, 5000));
	}

	entity.move(0, 0);

	sf::Vector2f movement(0.0f, 0.0f);
	movement.x += bulletSpeed;

	if (isBulletFiring)
	{
		if (getX() == 5000)
			SetPosition(sf::Vector2f(playerX, playerY));
	}

	entity.move(movement);
}
