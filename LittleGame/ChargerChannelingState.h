#pragma once
#ifndef CHARGERCHANNELINGSTATE_H
#define CHARGERCHANNELINGSTATE_H

#include "ChargerState.h"
#include "ChargerCHARGINGstate.h"

class ChargerChannelingState : public ChargerState
{
private:

public:
	ChargerChannelingState(EnemyObject& pHead, AIComponent& pBrain, float chargeUpTime_, float maxSpinSpeed_) 
		: ChargerState(pHead, pBrain, chargeUpTime_, maxSpinSpeed_) {
		this->pBrain->pushState(*this);
	}
	virtual void cleanUp() {

	}
	virtual void executeBehavior() {
		// Increase passed time
		this->passedTime += Locator::getGameTime()->getDeltaTime();

		// Rotate depending on how much we've charged up
		currentSpinSpeed = maxSpinSpeed * (this->passedTime / chargeUpTime);
		this->rotate(currentSpinSpeed);

		// Keep aiming for the player
		XMFLOAT3 myPos = this->pHead->GETPosition();
		XMFLOAT2 vecToPlayer = this->pHead->getVectorToPlayer();
		this->pBrain->SETsimulatedMovement(vecToPlayer);
		this->pHead->setDirection(XMFLOAT3(vecToPlayer.x, 0, vecToPlayer.y));

		// Check if we're done charging
		if (passedTime > chargeUpTime) {
			// Reset timer
			this->passedTime = 0;
			// Enable collisionDamage
			this->pHead->setIfCharged(true); 
			// Charge!
			EnemyState* newState = new ChargerChargingState(*pHead, *pBrain, this->chargeUpTime, this->maxSpinSpeed);
		}
	}
};


#endif 
