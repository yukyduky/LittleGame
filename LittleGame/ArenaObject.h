#pragma once
#ifndef ARENAOBJECT_H
#define ARENAOBJECT_H

#include "GameObject.h"



class ArenaObject : public GameObject
{
private:
	XMFLOAT3 startPos;
	float maxFallDepth = 0.0f;
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
