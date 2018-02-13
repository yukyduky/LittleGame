#pragma once
#ifndef ARENAOBJECT_H
#define ARENAOBJECT_H

#include "GameObject.h"



class ArenaObject : public GameObject
{
private:


public:
	ArenaObject(const size_t ID);
	ArenaObject(const size_t ID, XMFLOAT3 pos);
	virtual ~ArenaObject();
	
	virtual const size_t getID();
	// CURRENTLY EMPTY
	virtual void cleanUp();
	virtual void update();

};



#endif
