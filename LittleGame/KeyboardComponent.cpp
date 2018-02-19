#include "KeyboardComponent.h"
#include "GameObject.h"
#include "GamePlayState.h"
#include "Locator.h"
#include "Commands.h"


KeyboardComponent::KeyboardComponent(GameObject& obj) : ID(obj.getID())
{
	// Set up head
	this->pHead = dynamic_cast<ActorObject*>(&obj);
	this->pHead->SETinputComponent(this);

	POINT p;
	GetCursorPos(&p);
	this->cursorPos.x = p.x;
	this->cursorPos.y = p.y;

	this->init();
}

KeyboardComponent::KeyboardComponent(Menu& obj) : ID(1995)// hopefully this dosnt fak up
{
	// Set up head
	this->pHeadMenu = &obj;

	POINT p;
	GetCursorPos(&p);
	this->cursorPos.x = p.x;
	this->cursorPos.y = p.y;

	this->init();
}

void KeyboardComponent::update()
{
	this->generateCommands();
	this->execute();

	this->pHead->rotate(this->pHead->getPGPS()->GETMouseInput()->getWorldPosition());
}

const size_t KeyboardComponent::getID()
{
	return this->ID;
}

void KeyboardComponent::execute()
{
	for (auto &i : commandQueue) {
		i->execute(*this->pHead);
	}
	commandQueue.clear();
}

void KeyboardComponent::receive(GameObject & obj, Message msg)
{
}

void KeyboardComponent::cleanUp()
{
	this->keyboardCommandMap.clear();
	this->mouseCommandMap.clear();
	this->controllerCommandMap.clear();
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
