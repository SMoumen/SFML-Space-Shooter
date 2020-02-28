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
#include "Define.h"
#include <filesystem>
class StateMachine;

namespace fs = std::filesystem;

PlayingState::PlayingState(sf::Text &text,StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace }
{

	//Player information
	playerTexture.loadFromFile("Sprites/PlayerSprite.png");
	bulletTexture.loadFromFile("Sprites/BulletSprite.png");
	backgroundTexture.loadFromFile("Space1.jpg");

	int i = 0;

	const std::string path = "Asteroids/";
	
	for (const auto& file : fs::directory_iterator(path))
	{
		asteroidTextures[i].loadFromFile(file.path().string());
		i++;
	}
	player = std::make_unique<Player>(&playerTexture, sf::Vector2<unsigned>(9, 4), 0.05, 3);
	player->SetPosition(sf::Vector2<float>(screen_width / 2, screen_height / 2));
	backgroundSprite.setTexture(backgroundTexture);
	for(int i = 0; i < 5 ; i++)
	{

		asteroidVector.emplace_back(std::make_unique<Asteroids>(asteroidTextures[0],getNumberInRange(5.0f,5.0f), getNumberInRange(1, 2)));
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

void PlayingState::UpdateKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {

	if (time.asSeconds() >= 1.5)
	{

		if (key == sf::Keyboard::Space)
		{
			playerShooting = isPressed;
			bulletVector.emplace_back(std::make_unique<Bullet>(bulletTexture, player->getPosition()));
			dtClock.restart();
		}
	}
}

void PlayingState::UpdateEvents() {
	while (window.pollEvent(sfEvent)) {


		
			/*std::ofstream saveFile("SaveScore.txt", std::ios::app);
			saveFile << static_cast<std::string>(playerName.getString()) << "\t" << score << "\n";
		*/
		switch (sfEvent.type) {
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

void PlayingState::Update() {
	//fpsCounter.UpdateCounter();
	time = dtClock.getElapsedTime();
	cpt++;
	std::cout << time.asSeconds() << std::endl;
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
		for (auto& i : asteroidVector)
		{
			i->Update();
			if (i->IsColliding(*player))
			{
				//it = asteroidVector.erase(it);
				player->lifes--;
				i->SetPosition(sf::Vector2<float>(2000.0f, screen_height / 2.0f));
			}
			for(auto &b : bulletVector)
			{

				if(i->IsColliding(*b))
				{
					i->SetPosition(sf::Vector2f(getNumberInRange(2000, 20000), getNumberInRange(50, screen_height - 150)));

					b->marked = true;
					score++;
					std::cout << " Bullet collided \n";
				}
				
			}
		}
		for (auto it = bulletVector.begin(); it != bulletVector.end();)
		{
			it->get()->Update(playerShooting, 5, player->getX(), player->getY(), it->get()->marked);
			
			if (it->get()->marked == true || it->get()->getX() > screen_width)
			{
				it = bulletVector.erase(it);
				std::cout << " bullet destroyed \n";
			}
			else
				it++;

		}
		/*	for (auto it = bulletVector.begin(); it != bulletVector.end();)
			{
				it->get()->Update(playerShooting, 5, player->getX(), player->getY(), it->get()->marked);

				if (it->get()->marked == true)
				{
					it = bulletVector.erase(it);
					std::cout << " bullet destroyed \n";
				}

			}
			/*for (auto& i : bulletVector)
			{
				if (i->getX() > screen_width) {
					std::cout << " Bullet out of window\n";
					i->marked = true;
				}
				/*for (auto &a : asteroidVector)
				{
					if(a->IsColliding(*i))
					{
						i->marked = true;
						a->SetPosition(sf::Vector2f(getNumberInRange(2000, 20000), getNumberInRange(50, screen_height - 150)));
						score++;
					}
				}
			}*/

			/*for (auto it = bulletVector.begin(); it != bulletVector.end();)
			{

				it->get()->Update(playerShooting, 5, player->getX(), player->getY(), it->get()->marked);

				if (asteroidVector[i]->IsColliding(*it->get()))
				{
					//	pBullet->SetPosition(sf::Vector2<float>(2000.0f, screen_height / 2.0f));
					it->get()->marked = true;
					asteroidVector[i]->SetPosition(sf::Vector2f(getNumberInRange(2000, 20000), getNumberInRange(50, screen_height - 150)));


					asteroidVector.emplace_back(std::make_unique<Asteroids>(asteroidTextures[getNumberInRange(0, 3)], getNumberInRange(1.0f, 5.0f), getNumberInRange(1, 2)));

					score++;


				}

				++it;*/




	}

}

			
	

	


	


void PlayingState::Render() {
	window.clear();

	//Render items
//	fpsCounter.renderTo(window);
	//versionText.renderTo(window);
	//
	window.draw(backgroundSprite);
	//

	window.draw(playerName);
	for (auto const& i : asteroidVector)
	{
		i->RenderTo(window);
	}
for (auto const& i : bulletVector)
	{
		i->RenderTo(window);
}
			player->RenderTo(window);

			window.draw(scoretext);
			window.draw(lifeText);
	
		window.display();

}