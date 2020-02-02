#include "StateMachine.h"
#include "State.h"
#include <iostream>
#include <memory>



StateMachine::StateMachine()
	: stateResume{ false }
	, stateRunning{ false } {
}

void StateMachine::Run(std::unique_ptr<State> state) {
	stateRunning = true;
	states.push(std::move(state));
}

void StateMachine::NextState() {
	if (stateResume) {
		//Cleanup current state
		if (!states.empty()) { states.pop(); }

		stateResume = false;
	}

	if (!states.empty()) {
		std::unique_ptr<State> temp = states.top()->NextState();

		if (temp != nullptr) {
			if (temp->IsReplacing()) {
				states.pop();
			}

			states.push(std::move(temp));
		}
	}
}

void StateMachine::LastState() {
	stateResume = true;
}

void StateMachine::UpdateEvents() {
	states.top()->UpdateEvents();
}

void StateMachine::Update() {
	states.top()->Update();
}

void StateMachine::Render() {
	states.top()->Render();
}

bool StateMachine::IsRunning() {
	return stateRunning;
}

void StateMachine::Quit() {
	stateRunning = false;
}
