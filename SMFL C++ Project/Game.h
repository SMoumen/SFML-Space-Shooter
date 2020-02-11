#pragma once
#include "SFML/Graphics.hpp"

#include "StateMachine.h"
#include "MainMenuState.h"

class Game
{
public:
	Game() = default;

	void Run();

private:
	StateMachine machine;
	sf::RenderWindow window;
};
