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
	float passedTime = 0;
	float pulseInterval = 4.50;
	float maxVelocity = this->pHead->getVelocity();
	float timeFactor = maxVelocity / pulseInterval;

	float pulseFormula(float dt) {
		float returnValue = (maxVelocity - timeFactor * dt);
		// Let's not even have the possibility of negative velocity
		if (returnValue > 0)
			return returnValue;
		else
			return 0;
	}

protected:
	std::vector<EnemyObject*> neighbours;
	void adjustAim() {

		int degree = Locator::getRandomGenerator()->GenerateInt(-45, 45);
		XMFLOAT3 newDirection = this->pHead->getDirection();

		int radDegree = degree * PI / 180;

		newDirection.x += std::cos(radDegree);
		newDirection.z += std::sin(radDegree);
		this->pHead->setDirection(newDirection);
	}
	void pulse() {
		// Get time
		float dt = Locator::getGameTime()->getDeltaTime();
		this->passedTime += dt;

		// Adjust velocity based on time
		this->pHead->setVelocity(pulseFormula(this->passedTime));

		// Reset if necessary
		if (this->passedTime > pulseInterval) {
			this->passedTime = 0;
		}
	}
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
	bool inOrOutPlus() {
		XMFLOAT3 position = this->pHead->GETPosition();
		return this->pGrid->inOrOutPLUS(XMFLOAT2(position.x, position.z));
	}
	
public:
	SwarmerState(EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID) : EnemyState(pHead, pBrain) {
		this->pGrid = pGrid_;
		this->swarmerID = swarmerID;
	}
	virtual void removeFromGrid() {
		this->pGrid->removeSwarmer(this->swarmerID);
	}
	virtual void executeBehavior() = 0;
};

#endif
