#include "ArenaObject.h"
#include "Component.h"
#include "Locator.h"

ArenaObject::ArenaObject(const size_t ID)
	: GameObject(ID)
{
	this->counter = 0.0f;
	this->transitionTime = 5.0f;
}

ArenaObject::ArenaObject(const size_t ID, XMFLOAT3 pos)
	: GameObject(ID, pos)
{
	this->counter = 0.0f;
	this->transitionTime = 5.0f;
	this->startPos = pos;
	this->maxFallDepth = -500.0f;
}

ArenaObject::~ArenaObject()
{

}

const size_t ArenaObject::getID()
{
	return this->ID;
}

void ArenaObject::cleanUp()
{
	for (auto &c : this->components) {
		c->cleanUp();
		delete c;
	}
}

void ArenaObject::update()
{
	for (auto &i : this->components) {
		i->update();
	}	
}