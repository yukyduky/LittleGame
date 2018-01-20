#include "StateManager.h"
#include "State.h"

std::vector<State*> StateManager::sStates;

void StateManager::changeState(State* state)
{ 
	// If the state stack isn't empty
	if (!sStates.empty()) {
		// Cleanup the latest stack at the back
		sStates.back()->cleanup();
		// Remove the state from the back of the stack
		sStates.pop_back();
	}
	// Add the new state to the back of the stack
	sStates.push_back(state);
	// Initialize the new state
	sStates.back()->init();
}

void StateManager::popState()
{
	// If the state stack isn't empty
	if (!sStates.empty()) {
		// Cleanup the latest stack at the back
		sStates.back()->cleanup();
		// Remove the state from the back of the stack
		sStates.pop_back();
		// If the state stack still isn't empty
		if (!sStates.empty()) {
			// Resume the latest state at the back
			sStates.back()->resume();
		}
	}
}

void StateManager::pushState(State* state)
{ 
	// If the state stack isn't empty
	if (!sStates.empty()) {
		// Pause the current state
		sStates.back()->pause();
	}
	// Add the new state to the back of the stack
	sStates.push_back(state);
	// Initialize the new state
	sStates.back()->init();
}

void StateManager::handleEvents(GameManager* gm)
{
	sStates.back()->handleEvents(gm);
}

void StateManager::update(GameManager* gm)
{
	sStates.back()->update(gm);
}

void StateManager::render(GameManager* gm)
{
	sStates.back()->render(gm);
}

void StateManager::cleanup()
{
	for (auto &i : sStates) {
		i->cleanup();
	}
}
