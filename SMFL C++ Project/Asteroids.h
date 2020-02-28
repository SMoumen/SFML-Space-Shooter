#pragma once
#include "Entity.h"
class Bullet;

class Asteroids :
	public Entity
{
public:
	Asteroids(sf::Texture& texture, float speed, float x);
	Asteroids(const Asteroids&) = delete;
	Asteroids& operator =(const Asteroids&) = delete;
	~Asteroids();


	sf::Sprite sprite;
	bool IsColliding(Entity& entity) const;
	void Update();
	float speed;
};
