#pragma once
#include "State.h"
#include <array>
class StateMachine;

class MainMenuState : public State
{
public:

	MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
	~MainMenuState();

	void UpdateEvents() override;
	void Update() override;
	void Render() override;

private:
	//Variables

	//SFML
	sf::Event sfEvent;
	sf::Sprite playButton;
	sf::Text playerName;
	sf::String playerInput;
	std::array<sf::Texture, 4> textureArray;
	std::array<sf::Texture, 3> textureHoveredArray;

	std::array<sf::Sprite, 4> SpriteArray;
	sf::Font font;
	bool isNameDefined = false;
	bool isPressed = false;
};
