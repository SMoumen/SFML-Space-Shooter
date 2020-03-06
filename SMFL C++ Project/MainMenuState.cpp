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

MainMenuState::MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace) : State(
	machine, window, replace)

{
	TitleFont.loadFromFile(FONT_TITLE);
	Title.setFont(TitleFont);
	Title.setFillColor(sf::Color::White);
	Title.setString("Space Game Shooter");
	Title.setPosition((screen_width / 4)-50, 100);
	Title.setCharacterSize(72);
	
	std::cout << "MainMenuState";
	int i = 0;
	float j = 0.0f;

	const std::string path = "Textures/";
	const std::string pathHovered = "Hovered/";
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
		if (i != 0)

		{
			//SpriteArray[i].setOrigin(60,60);                                                             //(SpriteArray[i].getGlobalBounds().width / 2, SpriteArray[i].getGlobalBounds().height / 2);
			SpriteArray[i].setPosition(screen_width / 2.5f, (screen_height / 5.5f) + j);
		}
		i++;
		j += (screen_height / 5.0f);
	}
	font.loadFromFile("Arial.ttf");

	playerName.setFont(font);
	playerName.setFont(font);
	playerName.setPosition(screen_height / 2, screen_width / 2);
}

MainMenuState::~MainMenuState() = default;


void MainMenuState::UpdateEvents()
{
	//Events while loop
	while (window.pollEvent(sfEvent))
	{
		switch (sfEvent.type)
		{
		case sf::Event::Closed:
			machine.Quit();
			break;

		case sf::Event::MouseButtonPressed:
			if (is_pressed(SpriteArray[1], window))
			{
				isPressed = true;
			}
			if (is_pressed(SpriteArray[3], window)) { machine.Quit(); }
		case sf::Event::TextEntered:

			if (isPressed)
			{
				object.setFont(font);
				object.setPosition(screen_width / 2 - 100, screen_height / 2);
				object.setString("Enter your player name :\n");
				if (sfEvent.text.unicode < 128)
				{
					if (sfEvent.text.unicode == '\b' && playerInput.getSize() != 0)
					{
						playerInput.erase(playerInput.getSize() - 1, 1);
						playerName.setString(playerInput);
					}
					else if (sfEvent.text.unicode != ' ' && sfEvent.text.unicode != '\u0009' && sfEvent.text.unicode !=
						'\u0001' && sfEvent.text.unicode != '\u0000')
					{
						playerInput += sfEvent.text.unicode;
						
						
						playerName.setString(playerInput);
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						isNameDefined = true;
						machine.Run(machine.buildState<PlayingState>(playerName, machine, window, true));
						std::cout << "Playing State \n";
					}
				}
			}
		}
	}
}


void MainMenuState::Update()
{
	//fpsCounter.updateCounter();
	for (int i = 1; i < SpriteArray.size(); i++)
	{
		if (isHovered(SpriteArray[i], window))
		{
			SpriteArray[i].setTexture(textureHoveredArray[i - 1]);
		}

		else
		{
			SpriteArray[i].setTexture(textureArray[i]);
		}
	}
	window.draw(playerName);
}

void MainMenuState::Render()
{
	window.clear();
	if (isPressed == false)
	{
		for (sf::Sprite sprite : SpriteArray)
		{
			window.draw(sprite);
		}
		window.draw(Title);

	}

	
	window.draw(object);
	window.draw(playerName);
	window.display();
}
