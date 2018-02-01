#include "ArenaObject.h"


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
	this->cleanUp();
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
	int asdf = 3;
}