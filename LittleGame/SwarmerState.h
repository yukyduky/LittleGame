#pragma once
#ifndef SWARMERSTATE_H
#define SWARMERSTATE_H

#include "EnemyState.h"
#include "Grid.h"
#include "DirectXMath.h"

class EnemyObject;

class SwarmerState : public EnemyState
{
private:
	int what;
	Grid *grid = nullptr;

protected:
	EnemyObject * neighbours;
	void updateNeighbours(DirectX::XMFLOAT2 position) {
		//this->neighbours = this->grid.getNeighbours(position);
	}
	
public:
	virtual void executeBehavior() = 0;
};

#endif
