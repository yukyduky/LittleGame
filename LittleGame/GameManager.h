#pragma once
#ifndef RANDOMZENGINE_H
#define RANDOMZENGINE_H

#include <Windows.h>
#include <d3d11.h>
#include "IGameTime.h"

class State;

class GameManager
{
private:
	bool isRunning;
	IGameTime* gameTime;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the game window etc.*/
	void init(HINSTANCE hInstance, int nCmdShow);
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
