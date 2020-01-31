#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>

class State;

class StateMachine
{
public :

	StateMachine();

	void Run(std::unique_ptr<State> state);

	void NextState();
	void LastState();
	void UpdateEvents();

	void Update();
	void Render();

	bool IsRunning();
	void Quit();

	template <typename T>
	static std::unique_ptr<T> buildState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);


private :

	std::stack<std::unique_ptr<State>> states;

	bool stateResume;
	bool stateRunning;






};
template <typename T>
std::unique_ptr<T> StateMachine::buildState(StateMachine& machine, sf::RenderWindow& window, bool replace) {
	return std::unique_ptr<T>(new T(machine, window, replace));
}
