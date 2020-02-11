#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

#include <memory>

class StateMachine;

class State
{
public:
	State(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
	virtual ~State() = default;

	State(const State&) = delete;
	State& operator =(const State&) = delete;

	virtual void UpdateEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	std::unique_ptr<State> NextState();

	bool IsReplacing();


protected:
	StateMachine& machine;
	sf::RenderWindow& window;

	bool replacing;

	std::unique_ptr<State> next;
};
