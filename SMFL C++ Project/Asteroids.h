#pragma once
#include "Entity.h"
class Bullet;

class Asteroids :
	public Entity
{
public:
	Asteroids(sf::Texture& texture,float speed);
	Asteroids(const Asteroids&) = delete;
	Asteroids& operator =(const Asteroids&) = delete;
	~Asteroids();


	bool life = true;
	sf::Sprite sprite;
	bool Colliding(Entity &entity);
	void Update();
	float speed;
	int count;
	//void RenderTo(sf::RenderWindow& window) const;
};

