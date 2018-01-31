#include "KeyboardComponent.h"
#include "GameObject.h"
#include "Locator.h"
#include "Command.h"


KeyboardComponent::KeyboardComponent(GameObject& obj) : InputComponent(obj)
{
	POINT p;
	GetCursorPos(&p);
	this->cursorPos.x = p.x;
}

void KeyboardComponent::receive(GameObject & obj, Message msg)
{
}

void KeyboardComponent::generateCommands()
{
	// Keyboard
	// Iterates through all the keyboard keys that have a mapped command to them
	for (auto &it : this->keyboardCommandMap) {
		// GetAsyncKeyState returns true if key is pressed and it was not pressed last frame
		if (GetAsyncKeyState(it.first) && it.second.type == COMMANDTYPE::TAP) {
			this->commandQueue.push_back(it.second.command);
		}
		// GetKeyState returns true if key is pressed
		else if (GetKeyState(it.first) && it.second.type == COMMANDTYPE::HOLD) {
			this->commandQueue.push_back(it.second.command);
		}
	}

	// Mouse
	// Iterates through all the mouse keys that have a mapped command to them
	for (auto &it : this->mouseCommandMap) {
		if (GetAsyncKeyState(it.first) && it.second.type == COMMANDTYPE::TAP) {
			this->commandQueue.push_back(it.second.command);
		}
		else if (GetKeyState(it.first) && it.second.type == COMMANDTYPE::HOLD) {
			this->commandQueue.push_back(it.second.command);
		}
	}

	POINT p;
	// Gets the cursor pos relative to the screen
	GetCursorPos(&p);
	// Converts the cursor pos to relative to the window
	ScreenToClient(Locator::getD3D()->GEThwnd(), &p);

	this->cursorPos.x = p.x;
	this->cursorPos.y = p.y;
}

XMFLOAT2 KeyboardComponent::GETcursorPos()
{
	return this->cursorPos;
}
