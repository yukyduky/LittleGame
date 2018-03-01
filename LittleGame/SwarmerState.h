#pragma once
#ifndef SWARMERSTATE_H
#define SWARMERSTATE_H

#include "EnemyState.h"
#include "Grid.h"
#include "EnemyObject.h"
#include "DirectXMath.h"

class EnemyObject;

class SwarmerState : public EnemyState
{
private:
	size_t swarmerID = 0;
	Grid *pGrid = nullptr;

protected:
	std::vector<EnemyObject*> neighbours;
	void updateNeighbours(DirectX::XMFLOAT2 position) {
		this->neighbours = this->pGrid->getNeighbours(position);
	}
	size_t getSwarmerID() {
		return this->swarmerID;
	}
	XMFLOAT3 getPositionToSeek() {
		return this->pGrid->getPositionToSeek();
	}
	std::vector<EnemyObject*> getNeighbours() {
		return this->neighbours;
	}
	Grid* getGrid() {
		return this->pGrid;
	}
	// In = true | out = false
	bool inOrOut() {	
		XMFLOAT3 position = this->pHead->GETPosition();
		return this->pGrid->inOrOut(XMFLOAT2(position.x, position.z));
	}
	
public:
	SwarmerState(EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID) : EnemyState(pHead, pBrain) {
		this->pGrid = pGrid_;
		this->swarmerID = swarmerID;
	}
	virtual void executeBehavior() = 0;
};

#endif
