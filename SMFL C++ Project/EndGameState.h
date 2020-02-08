#pragma once
#include "State.h"
#include <array>
class EndGameState :
	public State
{

public:
	EndGameState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
	//EndGameState(const EndGameState&) = delete;
	//EndGameState& operator =(const EndGameState&) = delete;
	~EndGameState();

	void UpdateKeyboardInputs(sf::Keyboard::Key key, bool isPressed);

	void UpdateEvents() override;
	void Update() override;
	void Render() override;

private:

	std::array<sf::Texture, 4> textureArray;
	std::array <sf::Sprite, 4> spriteArray;

	sf::Sprite background;
	

	
};


