#pragma once
#ifndef CHARGERCHANNELINGSTATE_H
#define CHARGERCHANNELINGSTATE_H

#include "ChargerState.h"
#include "ChargerCHARGINGstate.h"

class ChargerChannelingState : public ChargerState
{
private:
	float passedTime = 0;
	float chargeUpTime = 5;

public:
	ChargerChannelingState(EnemyObject& pHead, AIComponent& pBrain) : ChargerState(pHead, pBrain) {
		this->pBrain->pushState(*this);
	}
	virtual void cleanUp() {

	}
	virtual void executeBehavior() {
		// Increase passed time
		passedTime += Locator::getGameTime()->getDeltaTime();

		// Affect rotation
	//	this->pHead->SETrotationMatrix();

		// Keep aiming for the player
		XMFLOAT3 myPos = this->pHead->GETPosition();
		XMFLOAT2 vecToPlayer = this->pHead->getVectorToPlayer();
		this->pBrain->SETsimulatedMovement(vecToPlayer);
		this->pHead->setDirection(XMFLOAT3(vecToPlayer.x, 0, vecToPlayer.y));

		// Check if we're done charging
		if (passedTime > chargeUpTime) {
			passedTime = 0;
			EnemyState* newState = new ChargerChargingState(*pHead, *pBrain);
		}
		// Charge!
	}
};


#endif 
