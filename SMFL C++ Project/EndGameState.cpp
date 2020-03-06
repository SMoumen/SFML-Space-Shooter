#include "EndGameState.h"
#include <filesystem>
#include "Define.h"
#include <iostream>
#include "Utility.h"

#include "State.h"
#include "StateMachine.h"
#include "PlayingState.h"
#include "MainMenuState.h"


namespace fs = std::filesystem;

EndGameState::EndGameState(StateMachine& machine, sf::RenderWindow& window, bool replace) : State(
	machine, window, replace)
{
	int i = 0;
	float j = 0.0f;

	const std::string path = "Textures/";
	const std::string pathHovered = "Hovered/";
	std::cout << "End Game State";

	for (const auto& file : fs::directory_iterator(path))
	{
		textureArray[i].loadFromFile(file.path().string());
		spriteArray[i].setTexture(textureArray[i]);
		if (i != 0)

		{
			spriteArray[i].setPosition(screen_width / 2.5f, (screen_height / 5.5f) + j);
		}
		i++;
		j += (screen_height / 5.0f);
	}

	font.loadFromFile(FONT_TITLE);
	defeatText.setPosition(screen_width / 3, screen_height / 3);
	defeatText.setFillColor(sf::Color::Yellow);
	defeatText.setCharacterSize(36);
	defeatText.setFont(font);
	defeatText.setString("You died! Wanna play again?\n");
	
}


EndGameState::~EndGameState() = default;

void EndGameState::UpdateKeyboardInputs(sf::Keyboard::Key key, bool isPressed)
{
	
}

void EndGameState::UpdateEvents()
{
	if(is_pressed(spriteArray[1],window))
	{
		machine.Run(machine.buildState<MainMenuState>(machine, window, true));


	}
	if(is_pressed(spriteArray[3],window))
	{
		machine.Quit();
	}
}

void EndGameState::Update()
{
}

void EndGameState::Render()
{
	window.clear();
	for (int i = 0; i < spriteArray.size();i++)
	{
		if(i%2 != 0)
		{
			window.draw(spriteArray[i]);
		}
	}
	window.draw(defeatText);
	window.display();
}
