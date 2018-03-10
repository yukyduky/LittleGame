#pragma once
#ifndef SWARMEROUTSIDESTATE_H
#define SWARMEROUTSIDESTATE_H

#include "SwarmerState.h"
#include "EnemyObject.h"
#include "AIComponent.h"
#include "SwarmerSeekingState.h"

class SwarmerOutsideState : public SwarmerState
{
private:
	XMFLOAT3 openingInTheArena = { 0, 0, 0.01 };
	EnemyState* nextState = nullptr;

public:
	SwarmerOutsideState(EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID, XMFLOAT3 openingInTheArena)
		: SwarmerState(pHead, pBrain, pGrid_, swarmerID)
	{
		this->pBrain->pushState(*this);
	}
	void cleanUp() {

	}
	void executeBehavior() {
		/// Move inside the grid (move towards the player)
		XMFLOAT2 vectorToOpening;
		XMFLOAT3 myPos3 = this->pHead->GETPosition();
		vectorToOpening.x = openingInTheArena.x - myPos3.x;
		vectorToOpening.y = openingInTheArena.z - myPos3.z;

		// Set SimulatedMovement & Direction
		this->pBrain->SETsimulatedMovement(vectorToOpening);
		this->pHead->setDirection(XMFLOAT3(vectorToOpening.x, 0, vectorToOpening.y));

		// Move!
		this->pBrain->pushCommand(AICOMMANDS::MOVE);

		// If we've come inside the grid, ACT LIKE IT.
		if (this->inOrOutPlus()) {
			EnemyState* seekingState = new SwarmerSeekingState(
				*this->pHead, *this->pBrain, this->getGrid(), this->getSwarmerID()
			);
			this->getGrid()->activateMe(this->getSwarmerID()); // can this be moved inside the constructor?
		}
	}
};
#endif
