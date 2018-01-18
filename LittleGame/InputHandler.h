#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <array>
#include "Command.h"
#include <Windows.h>
#include <map>
#include <unordered_map>
#include <Xinput.h>

// Possible input types: TAP = 1 click, HOLD = key/button continuously pressed
enum class COMMANDTYPE { TAP, HOLD };

namespace KEYBOARD {
	enum KEYS { NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, SIZE };
}
namespace CONTROLLER {
	//enum KEYS { A, B, X, Y, RSHOULDER, LSHOULDER, LTRIG, RTRIG, DPADUP, DPADDOWN, DPADLEFT, DPADRIGHT, START, BACK, LCLICK, RCLICK, LTHUP, LTHDOWN, LTHRIGHT, LTHLEFT, LTHUPLEFT, LTHUPRIGHT, LTHDOWNRIGHT, LTHDOWNLEFT, RTHUP, RTHDOWN, RTHRIGHT, RTHLEFT, RTHUPLEFT, RTHUPRIGHT, RTHDOWNRIGHT, RTHDOWNLEFT, SIZE };
	enum KEYS { DPADUP, DPADDOWN, DPADLEFT, DPADRIGHT, START, BACK, LTHCLICK, RTHCLICK, LSHOULDER, RSHOULDER, A, B, X, Y };
}

struct Key {
	Command* command;
	COMMANDTYPE type;

	Key(Command* command, COMMANDTYPE type) : command(command), type(type) {}
	Key(const Key &key) : command(key.command), type(key.type) {}
	Key() {}
};

class InputHandler
{
private:
	std::map<UINT, Key> commandMap;
	std::unordered_map<KEYBOARD::KEYS, UINT> keyboardMap;
	std::unordered_map<CONTROLLER::KEYS, UINT> controllerMap;
	
	void mapEnumToVKC();
	void updateKeyboard(std::vector<Command*> commandQueue);
	void updateControllers(std::vector<Command*> commandQueue);
public:
	InputHandler();
	void update(std::vector<Command*> commandQueue);
	void mapEnumToKey(KEYBOARD::KEYS enumKey, Key key);
	void remapVKCToKey(UINT vkc, Key key);
};

#endif
