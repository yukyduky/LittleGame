#pragma once
#ifndef RANDOMZENGINE_H
#define RANDOMZENGINE_H

#include "IGameTime.h"
#include <Windows.h>

class State;

class GameManager
{
private:
	bool isRunning;
	IGameTime* gameTime;

public:
	// Initialize the game window etc.
	void init();
	// Cleanup the engine
	void cleanup();

	// Change to the given state
	void changeState(State* state);

	// Handles the events according to the current state
	void handleEvents();
	// Poll for new events
	bool pollEvent(MSG &msg);
	// Updates according to the current state
	void update();
	// Renders according to the current state
	void render();
	// Clears, draws, and displays the current state
	void display(State* state);

	// True/False if game is running
	bool getIsRunning();
	// Sets isRunning to false
	void quit();
};

#endif
