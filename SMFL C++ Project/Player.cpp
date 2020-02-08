#include "Player.h"
#include "Player.h"

#include "define.h"


Player::Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: Entity(*texture) {

	this->speed = speed;
	lifes = 3;
	entity.setOrigin(entity.getGlobalBounds().width / 2, entity.getGlobalBounds().height / 2);
}

void Player::updatePlayer(bool continuous) {
	//Movement/Animation
	sf::Vector2<float> playerMovement(0.f, 0.f);
	using Key = sf::Keyboard::Key;
	auto keyDown = [](sf::Keyboard::Key k) { return sf::Keyboard::isKeyPressed(k); };

	if (keyDown(Key::W)) { playerMovement.y -= speed; moving = true; } // setDirection(Animation::Direction::up);    moving = true; }
	else if (keyDown(Key::A)) { playerMovement.x -= speed; moving = true; }//setDirection(Animation::Direction::left);  moving = true; }
	else if (keyDown(Key::S)) { playerMovement.y += speed;   moving = true; }//setDirection(Animation::Direction::down);  moving = true; }
	else if (keyDown(Key::D)) { playerMovement.x += speed; moving = true; }//setDirection(Animation::Direction::right); moving = true; }
	else { moving = false; }


	//animation.updateAnimation(continuous, moving);
	//entity.setTextureRect(animation.uvRect);
	entity.move(playerMovement);
}

/*void Player::setDirection(const Animation::Direction& direction) {
	animation.direction = direction;
}
*/

void Player::updateBorderBounds() {
	//Entity cannot go through the borders of the screen

	if (getX() <= 50.0f) { SetPosition(sf::Vector2<float>(50.0f, getY())); } //Left Side
	if (getX() >= screen_width - 50.0f) { SetPosition(sf::Vector2<float>(screen_width - 50.0f, getY())); } //Right Side
	if (getY() <= 50.0f) { SetPosition(sf::Vector2<float>(getX(),  50.0f)); } //Left Side
	if (getY() >= screen_height - 50.0f) {SetPosition(sf::Vector2<float>(getX(), screen_height -50.0f));}
}

