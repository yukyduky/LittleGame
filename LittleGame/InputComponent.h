#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "Component.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <DirectXMath.h>

using namespace DirectX;

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

enum class COMMANDTYPE { TAP, HOLD };

namespace KEYBOARD {
	enum KEY {
		NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		ESC,
		SIZE
	};
}

namespace CONTROLLER {
	enum KEY { DPADUP, DPADDOWN, DPADLEFT, DPADRIGHT, START, BACK, LTHUMB, RTHUMB, LTRIGGER, RTRIGGER, A, B, X, Y, LSHOULDER, RSHOULDER, SIZE };
}

namespace MOUSE {
	enum KEY { LEFTCLICK, RIGHTCLICK, MOVE, SIZE };
}

namespace INPUTTYPE {
	enum KEY { KEYBOARD, CONTROLLER };
}

struct Key {
	Command* command;
	COMMANDTYPE type;

	Key(Command* command, COMMANDTYPE type) : command(command), type(type) {}
	Key() {}
};

class InputComponent : public Component
{
private:
	static std::unordered_map<KEYBOARD::KEY, size_t> keyboardKeyMap;
	static std::unordered_map<MOUSE::KEY, size_t> mouseKeyMap;
	static std::unordered_map<CONTROLLER::KEY, size_t> controllerKeyMap;

	static void mapCommands();
	static void mapKeys();
	static void mapKeyCodesToEnums();
	

protected:
	static std::map<size_t, Key> keyboardCommandMap;
	static std::map<size_t, Key> mouseCommandMap;
	static std::map<size_t, Key> controllerCommandMap;

	std::vector<Command*> commandQueue;
	static Command* commands[Commands::Size];

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given Key struct to the given enumerated key
	*/
	static void mapKeyboardKeyToCommand(Key key, KEYBOARD::KEY enumKey);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given Key struct to the given enumerated key
	*/
	static void mapMouseKeyToCommand(Key key, MOUSE::KEY enumKey);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given Key struct to the given enumerated key
	*/
	static void mapControllerKeyToCommand(Key key, CONTROLLER::KEY enumKey);

	static void mapLeftThumbStickToCommand(Command* command);
	static void mapRightThumbStickToCommand(Command* command);
	static void mapLeftShoulderToCommand(Command* command);
	static void mapRightShoulderToCommand(Command* command);

public:
//	InputComponent(InputComponent& obj);
	
	//virtual void move() = 0;
	//virtual void rotate() = 0;
	//virtual void fireAbility0();
	//virtual void fireAbilityX();

	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;
	virtual void update();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	WARNING Has to be run once before any other use of this class WARNING
	1. Initializes the mappings between keycodes and enums
	*/
	static void init();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Checks what keys are pressed and if they were just pressed or if they're being held
	2. Adds the command to the command queue if the key has a command mapped to it
	*/
	virtual void generateCommands() = 0;
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Executes all the commands that have been stored in the command queue.
	*/
	virtual void execute() = 0;
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Makes the controller vibrate a variable amount in either left or right or both sides
		If the InputComponent is a keyboard then nothing happens
	*/
	virtual void vibrate(size_t left, size_t right);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given virtual key code to the given Key struct
	*/
	void remapKeyboardKey(size_t vkc, Key key);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given virtual key code to the given Key struct
	*/
	void remapMouseKey(size_t vkc, Key key);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given virtual key code to the given Key struct
	*/
	void remapControllerKey(size_t vkc, Key key);
	void resetKeyBindings();
	virtual XMFLOAT2 GETnormalizedVectorOfLeftStick();
	virtual XMFLOAT2 GETnormalizedVectorOfRightStick();
	virtual float GETnormalizedValueOfLeftTrigger();
	virtual float GETnormalizedValueOfRightTrigger();
	virtual XMFLOAT2 GETcursorPos();
};

#endif // !INPUTCOMPONENT_H
