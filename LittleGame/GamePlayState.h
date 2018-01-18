#pragma once
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"
#include <vector>
#include "Command.h"
#include "IInputHandler.h"

class Command;

class GamePlayState : public State
{
private:
	static GamePlayState sGamePlayState;

	std::vector<Input> commandQueue;
	Command* selectCommand;

	void mapKeys();
public:
	// Initialize this state
	virtual void init();
	// Cleanup this state
	virtual void cleanup();

	// Pause this state
	virtual void pause();
	// Resume this state
	virtual void resume();

	// Handle the events generated in this state
	virtual void handleEvents(GameManager* re);
	// Update this state
	virtual void update(GameManager* re);
	// Render this state
	virtual void render(GameManager* re);

	void commandSelect(size_t player);

	// Get the static instance of this state
	static GamePlayState* getInstance();
};

#endif // !GAMEPLAYSTATE_H
