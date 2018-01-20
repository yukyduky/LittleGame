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
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Checks to see if the 'State Stack' contains any 'State'(class) objects.
	2. Reset the current State, freeing up memory, and moving into an idle mode.
	3. REPLACE the current State with the 'State'(class), provided as parameter.
	4. Run the 'init()' function to startup the newly added State.
	*/
	static void changeState(State* state);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Checks to see if the 'State Stack' contains any 'State'(class) objects.
	2. Reset the current State, freeing up memory, and setting it to idle/standby.
	3. REMOVE the current 'State'(class) object from the stack.
	4. If the stack is not empty, Run the 'Resume()' for last State in the stack.
	*/
	static void popState();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Checks to see if the 'State Stack' contains any 'State'(class) objects.
	2. Reset the current State, freeing up memory, and setting it to idle/standby.
	3. ADD the 'State'(class) pointer, provided as parameter, to the top of the stack.
	4. Run the 'init()' function to startup the newly added State.
	*/
	static void pushState(State* state);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Call the 'handleEvents()' function found in the State at the back of the stack.
	*/
	static void handleEvents(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Call the 'update()' function found in the State at the back of the stack.
	*/
	static void update(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Call the 'render()' function found in the State at the back of the stack.
	*/
	static void render(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Call the 'cleanup()' function in all states currently in the stack.
	*/
	static void cleanup();
};

#endif
