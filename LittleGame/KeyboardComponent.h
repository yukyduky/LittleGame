#pragma once
#ifndef KEYBOARDCOMPONENT_H
#define KEYBOARDCOMPONENT_H

#include "InputComponent.h"
#include "ActorObject.h"
#include <DirectXMath.h>
#include "Menu.h"

using namespace DirectX;

class KeyboardComponent : public InputComponent
{
private:
	Menu * pHeadMenu = nullptr;
	ActorObject* pHead = nullptr;
	const size_t ID;
	XMFLOAT2 cursorPos;
public:
	KeyboardComponent(GameObject& obj);
	KeyboardComponent(Menu& obj);

	virtual void update();

	virtual const size_t getID();
	virtual void execute();
	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
	virtual void generateCommands();
	virtual XMFLOAT2 GETcursorPos();
};

#endif // !KEYBOARDCOMPONENT_H
