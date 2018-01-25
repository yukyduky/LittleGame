#pragma once
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"
#include <vector>
#include "Command.h"
#include "IInputHandler.h"
#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "GameObject.h"

class Command;

class GamePlayState : public State
{
private:
	static GamePlayState sGamePlayState;

	std::vector<Input> commandQueue;
	Command* selectCommand;

	RenderInputOrganizer rio;
	GameObject* go;
	GraphicsComponent* block;

	/*RenderInputOrganizer rio;
	GraphicsComponent* block;
	GameObject* go;*/

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calls the 'getInputHandler()' in-order to call the 'mapCommandToKeyboardKey()' function.
	2. Calls the 'getInputHandler()' in-order to call the 'mapCommandToControllerKey()' function.
	3. Calls the 'getInputHandler()' in-order to call the 'mapCommandToLeftThumbStick()' function.
	*/
	void mapKeys();
public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the 'GamePlayState'.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleanup the 'GamePlayState'; freeing memory, default settings, etc.
	*/
	virtual void cleanup();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Pause the 'GamePlayState'.
	*/
	virtual void pause();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Resume the 'GamePlayState'.
	*/
	virtual void resume();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Handle the events generated in the GamePlayState.
	*/
	virtual void handleEvents(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Update the GamePlayState.
	*/
	virtual void update(GameManager* gm);
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Render the 'GamePlayState'
	*/
	virtual void render(GameManager* gm);

	void commandSelect(size_t player);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Get the static instance of the 'GamePlayState'.
	*/
	static GamePlayState* getInstance();
};

#endif // !GAMEPLAYSTATE_H
