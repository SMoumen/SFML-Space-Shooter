#include "EndGameState.h"
#include <filesystem>
#include "Define.h"
#include <iostream>


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
			//SpriteArray[i].setOrigin(60,60);                                                             //(SpriteArray[i].getGlobalBounds().width / 2, SpriteArray[i].getGlobalBounds().height / 2);
			spriteArray[i].setPosition(screen_width / 2.5f, (screen_height / 5.5f) + j);
		}
		i++;
		j += (screen_height / 5.0f);
	}
}


EndGameState::~EndGameState()
{
}

void EndGameState::UpdateKeyboardInputs(sf::Keyboard::Key key, bool isPressed)
{
}

void EndGameState::UpdateEvents()
{
}

void EndGameState::Update()
{
}

void EndGameState::Render()
{
	for (auto i : spriteArray)
		window.draw(i);
	window.display();
}
