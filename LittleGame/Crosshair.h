#pragma once
#ifndef CROSSHAIR_h
#define CROSSHAIR_h

#include "Locator.h"
#include "ActorObject.h"


class Crosshair : public GameObject
{
private:
	ActorObject * player = nullptr;

	// Distance from plater
	float radius = 0.0f;

public:
	Crosshair(ActorObject* player, const size_t ID);
	~Crosshair();

	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
	virtual void update();
};

#endif // !CROSSHAIR_h

