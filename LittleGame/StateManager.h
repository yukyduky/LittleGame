#pragma once
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>

class State;
class GameManager;

class StateManager
{
private:
	static std::vector<State*> sStates;

public:
	static void changeState(State* state);
	static void popState();
	static void pushState(State* state);
	static void handleEvents(GameManager* re);
	static void update(GameManager* re);
	static void render(GameManager* re);
};

#endif
