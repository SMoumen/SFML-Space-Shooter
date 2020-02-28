#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "Bullet.h"

class Player : public Entity
{
public:
	Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);

	void updatePlayer(bool continuous);
	//	void setDirection(const Animation::Direction& direction);
	void updateBorderBounds();

	std::vector<std::unique_ptr<Bullet>> BulletVector;
	int lifes;
private:
	//Animation animation;
	float speed;

	bool moving = false;
};
