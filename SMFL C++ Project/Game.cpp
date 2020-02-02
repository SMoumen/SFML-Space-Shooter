#include "Game.h"
#include "Define.h"


void Game::Run() {
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Framework!");
	window.setPosition({ window.getPosition().x, window.getPosition().y - 40 });
	window.setFramerateLimit(FRAMERATE_LIMIT);

	machine.Run(StateMachine::buildState<MainMenuState>(machine, window, true));
	//test

	printf(" Main menu state !! ");
	//Main Game Loop
	while (window.isOpen() && machine.IsRunning()) {
		machine.NextState();
		machine.UpdateEvents();
		machine.Update();
		machine.Render();
	}
}
