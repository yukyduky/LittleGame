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

struct Key {
	Command* command;
	COMMANDTYPE type;

	Key(Command* command, COMMANDTYPE type) : command(command), type(type) {}
	Key() {}
};

class InputComponent : public Component
{
private:
	const size_t ID;

	static std::unordered_map<KEYBOARD::KEY, size_t> keyboardKeyMap;
	static std::unordered_map<MOUSE::KEY, size_t> mouseKeyMap;
	static std::unordered_map<CONTROLLER::KEY, size_t> controllerKeyMap;

	static void mapKeyCodesToEnums();
protected:
	static std::map<size_t, Key> keyboardCommandMap;
	static std::map<size_t, Key> mouseCommandMap;
	static std::map<size_t, Key> controllerCommandMap;

	std::vector<Command*> commandQueue;
public:
	InputComponent(GameObject& obj);
	const size_t getID();
	virtual void receive(GameObject & obj, Message msg) = 0;
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
	1. Executes all the commands that have been stored in the command queue
	*/
	void execute();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Makes the controller vibrate a variable amount in either left or right or both sides
		If the InputComponent is a keyboard then nothing happens
	*/
	virtual void vibrate(size_t left, size_t right);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given Key struct to the given enumerated key
	*/
	void mapKeyboardKeyToCommand(Key key, KEYBOARD::KEY enumKey);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given Key struct to the given enumerated key
	*/
	void mapMouseKeyToCommand(Key key, MOUSE::KEY enumKey);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Maps the given Key struct to the given enumerated key
	*/
	void mapControllerKeyToCommand(Key key, CONTROLLER::KEY enumKey);
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
