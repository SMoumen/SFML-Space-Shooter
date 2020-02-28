#include "Entity.h"

#include "define.h"


Entity::Entity(sf::Texture& texture)
{
	entity.setTexture(texture);
}

void Entity::RenderTo(sf::RenderWindow& window) const
{
	window.draw(entity);
}

void Entity::SetPosition(sf::Vector2<float> newPos)
{
	entity.setPosition(newPos);
}

sf::Vector2f Entity::getPosition()
{
	return sf::Vector2<float>(getX(), getY());
}

float Entity::getX() const
{
	return entity.getPosition().x;
}

float Entity::getY() const
{
	return entity.getPosition().y;
}

sf::FloatRect Entity::getGlobalBounds() const
{
	return entity.getGlobalBounds();
}
