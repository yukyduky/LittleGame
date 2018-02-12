#pragma once
#ifndef CROSSHAIR_h
#define CROSSHAIR_h

#include "Locator.h"
#include "ActorObject.h"


class Crosshair : public GameObject
{
public:
	Crosshair(ActorObject* player, const size_t ID, XMFLOAT3 color);
	~Crosshair();

	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
	virtual void update();

private:
	ActorObject * player;
	XMFLOAT3 color;

	float radius;
};

Crosshair::Crosshair(ActorObject* player, const size_t ID, XMFLOAT3 color) : GameObject(ID)
{
	this->player = player;
	this->color = color;
	this->type = OBJECTTYPE::DOODAD;

	this->radius = 50;
}

Crosshair::~Crosshair()
{
}

void Crosshair::receive(GameObject & obj, Message msg)
{

}

void Crosshair::cleanUp()
{
	// Cleanup all the components
	for (auto &c : this->components) {
		c->getID();
		c->cleanUp();
		delete c;
	}

}

void Crosshair::update()
{
	this->setPosition(this->player->GETPosition() + (this->player->getDirection() * this->radius));
	this->SETrotationMatrix(this->player->getRotationMatrix());
	for (auto &i : this->components) {
		i->update();
	}
}


#endif // !CROSSHAIR_h

