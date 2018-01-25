#pragma once
#ifndef IINPUTHANDLER_H
#define IINPUTHANDLER_H

#include <vector>

class Command;

enum class COMMANDTYPE { TAP, HOLD };

struct point {
	float x;
	float y;
};

namespace KEYBOARD {
	enum KEYS { 
		NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		ESC, 
		SIZE
	};
}

namespace CONTROLLER {
	enum KEYS { DPADUP, DPADDOWN, DPADLEFT, DPADRIGHT, START, BACK, LTHUMB, RTHUMB, LTRIGGER, RTRIGGER, A, B, X, Y, LSHOULDER, RSHOULDER, SIZE };
}

namespace MOUSE {
	enum KEYS { LEFTCLICK, RIGHTCLICK, MOVE, SIZE };
}

struct Key {
	Command* command;
	COMMANDTYPE type;

	Key(Command* command, COMMANDTYPE type) : command(command), type(type) {}
	Key() {}
};

struct Input {
	Command* command;
	size_t player;

	Input(Command* command, size_t player) : command(command), player(player) {}
};

class IInputHandler
{
public:
	virtual void update(std::vector<Input>& commandQueue) = 0;
	virtual void mapCommandToKeyboardKey(KEYBOARD::KEYS enumKey, Key key) = 0;
	virtual void mapCommandToMouseKey(MOUSE::KEYS enumKey, Key key) = 0;
	virtual void mapCommandToControllerKey(CONTROLLER::KEYS enumKey, Key key) = 0;
	virtual void mapCommandToLeftThumbStick(Command* command) = 0;
	virtual void mapCommandToRightThumbStick(Command* command) = 0;
	virtual void mapCommandToLeftShoulder(Command* command) = 0;
	virtual void mapCommandToRightShoulder(Command* command) = 0;
	virtual void remapKeyboardKey(size_t vkc, Key key) = 0;
	virtual void remapControllerKey(size_t vkc, Key key) = 0;
	virtual void resetKeyBindings() = 0;
	virtual void vibrate(size_t controllerID, int left, int right) = 0;

	virtual void SETlastMouseCoordinates(point pt) = 0;
	virtual void SETnewMouseCoordinates(point pt) = 0;
	virtual point GETlastMouseCoordinates() = 0;
	virtual point GETnewMouseCoordinates() = 0;
	virtual point GETcontrollerMovement() = 0;
	virtual point GETcontrollerRotation() = 0;
};

#endif
