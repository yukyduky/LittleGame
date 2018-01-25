#pragma once
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"
#include <vector>
#include "Command.h"
#include "IInputHandler.h"

// If mingling with a POINT, just use x's and y's rather than mingling the entire structs

class Command;
enum Commands
{
	SELECT, MOUSEMOVE, CONTROLLERMOVE, CONTROLLERROTATE, 
	MOVEUP, MOVEDOWN, MOVELEFT, MOVERIGHT,
	SELECTABILITY1, SELECTABILITY2, SELECTABILITY3, SELECTABILITY4,
	FIREABILITY0, FIREABILITYX, 
	OPENMENU0, OPENMENU1, 
	Size
};

class GamePlayState : public State
{
private:
	static GamePlayState sGamePlayState;

	Command* commands[Commands::Size];
	std::vector<Input> commandQueue;


	void mapCommands();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calls the 'getInputHandler()' in-order to call the 'mapCommandToKeyboardKey()' function.
	2. Calls the 'getInputHandler()' in-order to call the 'mapCommandToControllerKey()' function.
	3. Calls the 'getInputHandler()' in-order to call the 'mapCommandToLeftThumbStick()' function.
	*/
	void mapKeys();

	void initInputMapping();

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
	void commandMoveUp();
	void commandMoveLeft();
	void commandMoveDown();
	void commandMoveRight();
	void commandSelectAbility1();
	void commandSelectAbility2();
	void commandSelectAbility3();
	void commandSelectAbility4();
	void commandFireAbility0();
	void commandFireAbilityX();
	void commandMouseRotation();

	void commandControllerMovement();
	void commandControllerRotation();

	void commandOpenMenu0();
	void commandOpenMenu1();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Get the static instance of the 'GamePlayState'.
	*/
	static GamePlayState* getInstance();
};

#endif // !GAMEPLAYSTATE_H
