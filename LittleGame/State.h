#pragma once
#ifndef STATE_H
#define STATE_H

class GameManager;

class State
{
public:
	// Initialize this state
	virtual void init() = 0;
	// Cleanup this state
	virtual void cleanup() = 0;

	// Pause this state
	virtual void pause() = 0;
	// Resume this state
	virtual void resume() = 0;

	// Handle the events generated in this state
	virtual void handleEvents(GameManager* re) = 0;
	// Update this state
	virtual void update(GameManager* re) = 0;
	// Render this state
	virtual void render(GameManager* re) = 0;
};

#endif
