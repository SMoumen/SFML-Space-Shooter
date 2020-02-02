#pragma once
#include "State.h"
#include <array>
class StateMachine;
class MainMenuState : public State {
public:

	MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
	~MainMenuState();

	void UpdateEvents();
	void Update();
	void Render();

private:
	//Variables



	//Class objects
	//FPSCounter fpsCounter;
	//Button startGameButton, quitGameButton;
	//Text titleText;


	//SFML
	sf::Event sfEvent;
	sf::Sprite playButton;
	std::array<sf::Texture, 4> textureArray;
	std::array<sf::Texture, 3> textureHoveredArray;

	std::array<sf::Sprite,4> SpriteArray;
};


