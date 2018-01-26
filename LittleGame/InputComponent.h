#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "Component.h"
#include <vector>
#include <unordered_map>
#include <map>

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

	void mapKeyCodesToEnums();
protected:
	static std::map<size_t, Key> keyboardCommandMap;
	static std::map<size_t, Key> mouseCommandMap;
	static std::map<size_t, Key> controllerCommandMap;

	std::vector<Command*> commandQueue;
public:
	InputComponent(GameObject& obj);
	const size_t getID();
	virtual void receive(GameObject & obj, Message msg) = 0;
	virtual void generateCommands() = 0;
	virtual void execute()= 0;
	virtual void vibrate(size_t left, size_t right);
	void mapKeyboardKeyToCommand(Key key, KEYBOARD::KEY enumKey);
	void mapMouseKeyToCommand(Key key, MOUSE::KEY enumKey);
	void mapControllerKeyToCommand(Key key, CONTROLLER::KEY enumKey);
	void remapKeyboardKey(size_t vkc, Key key);
	void remapControllerKey(size_t vkc, Key key);
	void resetKeyBindings();
};

#endif // !INPUTCOMPONENT_H
