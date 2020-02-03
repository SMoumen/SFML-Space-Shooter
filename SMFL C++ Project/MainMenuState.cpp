#include "MainMenuState.h"
#include "Utility.h"
#include "State.h"
#include "StateMachine.h"
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "Define.h"
#include <experimental/filesystem>
#include <iostream>
#include "PlayingState.h"
#include <fstream>

namespace fs = std::experimental::filesystem;

MainMenuState::MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace ) : State(machine,window,replace)

{

	int i = 0;
	float j = 0.0f;

	std::string path = "Textures/";
	std::string pathHovered = "Hovered/";
	int k = 0;
	for (const auto& file : fs::directory_iterator(pathHovered))
	{
		textureHoveredArray[k].loadFromFile(file.path().string());
		k++;
	}

	for (const auto& file : fs::directory_iterator(path))
	{	
		textureArray[i].loadFromFile(file.path().string());
		SpriteArray[i].setTexture(textureArray[i]);
		if (i !=0)

		{
			//SpriteArray[i].setOrigin(60,60);                                                             //(SpriteArray[i].getGlobalBounds().width / 2, SpriteArray[i].getGlobalBounds().height / 2);
			SpriteArray[i].setPosition(SCREEN_WIDTH / 2.5f, (SCREEN_HEIGHT / 5.5f) + j);

		}
		i++;
		j += (SCREEN_HEIGHT /5.0f);
	}
	
	
}

MainMenuState::~MainMenuState() {
	//
}

void MainMenuState::UpdateEvents() {
	sf::Vector2<int> mousepos = sf::Mouse::getPosition(window);

	/*Updating mouse position for button functionality
	startGameButton.update(sf::Vector2<float>(mousepos));
	quitGameButton.update(sf::Vector2<float>(mousepos));
	*/

	//Events while loop
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
		case sf::Event::Closed:
			machine.Quit();
			break;

				case sf::Event::MouseButtonPressed:
					if (isPressed(SpriteArray[1], window)) { machine.Run(machine.buildState<PlayingState>(machine, window, true)); }
					if (isPressed(SpriteArray[3], window)) { machine.Quit(); }

				
		}
		}

}



void MainMenuState::Update() {
	//fpsCounter.updateCounter();

	for (int i= 1;i < SpriteArray.size();i++)
	{
		if (isHovered(SpriteArray[i], window))
		{
			SpriteArray[i].setTexture(textureHoveredArray[i-1]);
		}

		else {

			SpriteArray[i].setTexture(textureArray[i]);

		}

	}
}

void MainMenuState::Render() {
	window.clear();
	

	
	//Render items
//	startGameButton.renderTo(window);
//	quitGameButton.renderTo(window);
	for (sf::Sprite sprite : SpriteArray) {
		window.draw(sprite);
	}
//	titleText.renderTo(window);
//	fpsCounter.renderTo(window);


	window.display();
}
