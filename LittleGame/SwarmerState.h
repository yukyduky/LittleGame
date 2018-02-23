#pragma once
#ifndef SWARMERSTATE_H
#define SWARMERSTATE_H

#include "EnemyState.h"
#include "State.h"
//#include "Grid.h"

class EnemyObject;

class SwarmerState : public EnemyState
{
private:
//	Grid grid;

protected:
	EnemyObject * neighbours;
	void updateNeighbours() {
		
	}
	
public:
	virtual void executeBehavior() = 0;
};

#endif
