#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"
#include "Player.h"
#include	"MainMenuState.h"
#include "Asteroids.h"
#include <iostream>
#include <sstream>
#include "Utility.h"
#include "EndGameState.h"
#include <fstream>

class StateMachine;

#include "Define.h"

PlayingState::PlayingState(sf::Text& text, StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{machine, window, replace}
{
	playerTexture.loadFromFile("Sprites/PlayerSprite.png");
	bulletTexture.loadFromFile("Sprites/BulletSprite.png");
	backgroundTexture.loadFromFile("Space1.jpg");
	asteroidTexture.loadFromFile("Sprites/AsteroidSprite.png");
	player = std::make_unique<Player>(&playerTexture, sf::Vector2<unsigned>(9, 4), 0.05, 5);
	pBullet = std::make_unique<Bullet>(bulletTexture);
	pBullet->SetPosition(sf::Vector2<float>(5000, 5000));
	player->SetPosition(sf::Vector2<float>(screen_width / 2, screen_height / 2));
	backgroundSprite.setTexture(backgroundTexture);
	for (int i = 0; i < 1; i++)
	{
		asteroidVector.emplace_back(std::make_unique<Asteroids>(asteroidTexture, getNumberInRange(5.0f, 5.0f)));
	}


	font.loadFromFile("Arial.ttf");

	lifeText.setFont(font);
	scoretext.setFont(font);

	scoretext.setPosition(50, 0);
	lifeText.setPosition(50, 50);
	scoretext.setFillColor(sf::Color::White);

	playerName.setFont(font);
	playerName.setPosition(0, 0);
	playerName = text;


	window.draw(playerName);


	isGamePaused = false;
}

PlayingState::~PlayingState() = default;

void PlayingState::UpdateKeyboardInputs(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Space) { playerShooting = isPressed; }
}

void PlayingState::UpdateEvents()
{
	while (window.pollEvent(sfEvent))
	{
		switch (sfEvent.type)
		{
		case sf::Event::Closed:
			machine.Quit();
			break;

		case sf::Event::KeyPressed:
			//Pausing the game upon pressing escape 

			if (sfEvent.key.code == sf::Keyboard::Escape && isGamePaused == false)
			{
				isGamePaused = true;
			}
			else if (sfEvent.key.code == sf::Keyboard::Escape && isGamePaused == true)
			{
				isGamePaused = false;
			}
			UpdateKeyboardInputs(sfEvent.key.code, true);
			break;

		case sf::Event::KeyReleased:
			UpdateKeyboardInputs(sfEvent.key.code, false);
			break;
		}
	}
}

void PlayingState::Update()
{
	/*------------------------------------------------------------------------------------------------------------------*/
	//Generalized Updating
	if (asteroidVector.empty() || player->lifes <= 0)
	{
		isGamePaused = true;
		isGameOver = true;
		std::ofstream saveFile("SaveScore.txt", std::ios::app);
		std::string s1 = playerName.getString();
		std::cout << " Player name : " << s1;
		s1.erase(std::remove(s1.begin(), s1.end(), '\n'), s1.end());
		s1.erase(std::remove(s1.begin(), s1.end(), '\r'), s1.end());
		saveFile << score << '\t' << s1 << '\n';
		machine.Run(machine.buildState<MainMenuState>(machine, window, true));
	}
	playerName.setCharacterSize(15);
	playerName.setPosition(player->getX() - 50, player->getY() - 50);
	scoretext.setString(" score : " + std::to_string(score));
	lifeText.setString("Lives : " + std::to_string(player->lifes));
	if (isGamePaused == false)
	{
		player->updateBorderBounds();
		player->updatePlayer(false);
		pBullet->Update(playerShooting, 15, player->getX(), player->getY());


		for (auto it = asteroidVector.begin(); it != asteroidVector.end();)
		{
			it->get()->Update();
			if (it->get()->IsColliding(*player))
			{
				//it = asteroidVector.erase(it);
				player->lifes--;
				it->get()->SetPosition(sf::Vector2<float>(2000.0f, screen_height / 2.0f));
			}
			if (it->get()->IsColliding(*pBullet))
			{
				pBullet->SetPosition(sf::Vector2<float>(2000.0f, screen_height / 2.0f));

				it = asteroidVector.erase(it);

				std::cout << score << std::endl;
			}
			else
			{
				++it;
			}
		}
	}
}


void PlayingState::Render()
{
	window.clear();

	window.draw(backgroundSprite);


	window.draw(playerName);
	for (auto const& i : asteroidVector)
	{
		i->RenderTo(window);
	}
	player->RenderTo(window);
	pBullet->RenderTo(window);

	window.draw(scoretext);
	window.draw(lifeText);

	window.display();
}
