#pragma once
#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include "InputComponent.h"
#include <Windows.h>
#include <Xinput.h>
#include <DirectXMath.h>
#include "ActorObject.h"

using namespace DirectX;

class ControllerComponent : public InputComponent
{
private:
	ActorObject* pHead = nullptr;
	enum class THUMB { LTHUMB, RTHUMB };

	size_t controllerID;
	XINPUT_STATE currentState;
	XMFLOAT2 thumbLDir;
	XMFLOAT2 thumbRDir;
	float trigLValue = 0.0f;
	float trigRValue = 0.0f;

	float checkThumb(THUMB thumb, size_t deadzone, XINPUT_STATE state);
public:
	
	ControllerComponent(GameObject& obj, size_t controllerID);
	virtual ~ControllerComponent() {}
	virtual void update();
	virtual void execute();
	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
	virtual void generateCommands();
	virtual void vibrate(unsigned short left, unsigned short right);
	virtual XMFLOAT2 GETnormalizedVectorOfLeftStick();
	virtual XMFLOAT2 GETnormalizedVectorOfRightStick();
	virtual float GETnormalizedValueOfLeftTrigger();
	virtual float GETnormalizedValueOfRightTrigger();
	virtual const size_t getID();
};

#endif // !CONTROLLERCOMPONENT_H
