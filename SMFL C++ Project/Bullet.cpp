#include "Bullet.h"
#include "Define.h"

Bullet::Bullet(sf::Texture& texture, sf::Vector2<float> vect) : Entity(texture)
{
	entity.setOrigin(float(texture.getSize().x / 2), texture.getSize().y / 2);
	entity.setPosition(vect.x, vect.y);
}


void Bullet::Update(bool isBulletFiring, int bulletSpeed, int playerX, int playerY, bool marked)
{
	if (marked == false)
	{
		sf::Vector2f movement(0.0f, 0.0f);
		movement.x += bulletSpeed;
		entity.move(movement);
	}
}
