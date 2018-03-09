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
public:
	SwarmerOutsideState(EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID)
		: SwarmerState(pHead, pBrain, pGrid_, swarmerID)
	{
		this->pBrain->pushState(*this);
	}
	void cleanUp() {

	}
	void executeBehavior() {
		/// Move inside the grid (move towards the player)
		XMFLOAT2 vectorToPlayer = this->pHead->getVectorToPlayer();

		// Set SimulatedMovement & Direction
		this->pBrain->SETsimulatedMovement(vectorToPlayer);
		this->pHead->setDirection(XMFLOAT3(vectorToPlayer.x, 0, vectorToPlayer.y));

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
