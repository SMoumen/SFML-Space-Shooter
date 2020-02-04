#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"
#include "Player.h"
#include	"MainMenuState.h"


class StateMachine;

#include "Define.h"

PlayingState::PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{


	//Player information
	playerTexture.loadFromFile("Sprites/PlayerSprite.png");
	bulletTexture.loadFromFile("Sprites/BulletSprite.png");
	backgroundTexture.loadFromFile("Sprites/BackgroundSprite.jpg");
	
	player = std::make_unique<Player>(&playerTexture, sf::Vector2<unsigned>(9, 4), 0.05, 1.5);
	pBullet = std::make_unique<Bullet>(bulletTexture);
	pBullet->SetPosition(sf::Vector2<float>(5000, 5000));
	player->SetPosition(sf::Vector2<float>(screen_width / 2, screen_height / 2));
	GamePaused = false;
	


}

PlayingState::~PlayingState() = default;

void PlayingState::UpdateKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	/*if (sf::Keyboard::isKeyPressed())
	{

		GamePa used = true;
		std::cout << "Game paused\n";
		return;
	}
	else if (key == sf::Keyboard::Escape && GamePaused == true)
	{
		GamePaused = false;
		std::cout << "Game unpaused\n";
		return;

	}*/
		//machine.Run(machine.buildState<MainMenuState>(machine, window, true)); }
	if (key == sf::Keyboard::Space) { playerShooting = isPressed; }
}

void PlayingState::UpdateEvents() {
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
		case sf::Event::Closed:
			machine.Quit();
			break;

		case sf::Event::KeyPressed:
			//Pausing the game upon pressing escape 

			if (sfEvent.key.code == sf::Keyboard::Escape  && GamePaused == false)
			{
				GamePaused = true;
			}
			else if (sfEvent.key.code == sf::Keyboard::Escape && GamePaused == true)
			{
				GamePaused = false;
			}
			UpdateKeyboardInputs(sfEvent.key.code, true);
			break;

		case sf::Event::KeyReleased:
			UpdateKeyboardInputs(sfEvent.key.code, false);
			break;
		}
	}
}

void PlayingState::Update() {
	//fpsCounter.UpdateCounter();

	/*------------------------------------------------------------------------------------------------------------------*/
	//Generalized Updating
	if (GamePaused == false)
	{


		player->updateBorderBounds();
		player->updatePlayer(false);
		pBullet->Update(playerShooting, 15, player->getX(), player->getY());

	}
	/*-------------------------------------------------------------------------------------------------------------------*/


}

void PlayingState::Render() {
	window.clear();

	//Render items
//	fpsCounter.renderTo(window);
	//versionText.renderTo(window);
	player->RenderTo(window);
	pBullet->RenderTo(window);

	window.display();
}