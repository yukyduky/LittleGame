#include "ArenaObject.h"
#include "Component.h"

ArenaObject::ArenaObject(const size_t ID)
	: GameObject(ID)
{

}

ArenaObject::ArenaObject(const size_t ID, XMFLOAT3 pos)
	: GameObject(ID, pos)
{

}

ArenaObject::~ArenaObject()
{

}

const size_t ArenaObject::getID()
{
	return this->ID;
}

void ArenaObject::receive(GameObject &obj, Message msg)
{

}

void ArenaObject::cleanUp()
{
	for (auto &c : this->components) {
		c->getID();
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