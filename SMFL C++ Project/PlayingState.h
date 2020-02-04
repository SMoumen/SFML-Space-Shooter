#pragma once
#include "State.h"
#include "Bullet.h"


class Player;

class PlayingState :
	public State
{
public :
	PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	~PlayingState();

	void UpdateKeyboardInputs(sf::Keyboard::Key key, bool isPressed);

	void UpdateEvents() override;
	void Update() override;
	void Render() override;

private:
	//Variables and Booleans


	//Arrays


	//Vectors


	//Class objects
	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<Bullet> pBullet = nullptr;
	bool GamePaused;
	//	FPSCounter fpsCounter;
	//	Text versionText;
	bool playerShooting;

	//SFML
	sf::Event sfEvent;
	sf::Texture playerTexture;
	sf::Texture bulletTexture;
	sf::Clock dtClock;
	sf::Texture backgroundTexture;
};
