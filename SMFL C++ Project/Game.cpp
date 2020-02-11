#include "Game.h"
#include "Define.h"
#include "EndGameState.h"

void Game::Run()
{
	window.create(sf::VideoMode(screen_width, screen_height), "SFML Framework!");
	window.setPosition({window.getPosition().x, window.getPosition().y - 40});
	window.setFramerateLimit(framerate_limit);

	machine.Run(StateMachine::buildState<MainMenuState>(machine, window, true));
	//test


	//Main Game Loop
	while (window.isOpen() && machine.IsRunning())
	{
		machine.NextState();
		machine.UpdateEvents();
		machine.Update();
		machine.Render();
	}
}
