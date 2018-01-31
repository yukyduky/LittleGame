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

void ArenaObject::cleanUp()
{
	int asdf = 3;
}