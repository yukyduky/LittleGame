#pragma once
#ifndef CROSSHAIR_h
#define CROSSHAIR_h

#include "Locator.h"
#include "ActorObject.h"


class Crosshair : public GameObject
{
public:
	Crosshair(ActorObject* player, const size_t ID);
	~Crosshair();

	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
	virtual void update();

private:
	ActorObject * player;
	
	// Distance from plater
	float radius;
};

#endif // !CROSSHAIR_h

