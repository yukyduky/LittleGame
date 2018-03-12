#pragma once
#ifndef CHARGERCHARGINGSTATE_H
#define CHARGERCHARGINGSTATE_H

#include "ChargerState.h"

class ChargerChargingState : public ChargerState
{
	// These are used so that this states timer lines up (closely enough) with the earlier
	// states timer without the need for passing variables between them.
	float passedTime = 0;
	float paddingTime = passedTime + 0.5;

	// The faster movement and lower framerate makes this state require even heavier padding
	bool inOrOutPRIVATE() {
		XMFLOAT3 position = this->pHead->GETPosition();
		bool result = false;
		int margin = ARENADATA::GETlengthOfWall() + ARENADATA::GETsquareSize() * 2;

		if ((position.x > margin) && (position.x < ARENADATA::GETarenaWidth() - margin)) {
			if ((position.z > margin) && (position.z < ARENADATA::GETarenaHeight() - margin)) {
				result = true;
			}
		}

		return result;
	}

public:
	ChargerChargingState(EnemyObject& pHead, AIComponent& pBrain, float chargeUpTime_, float maxSpinSpeed_) 
		: ChargerState(pHead, pBrain, chargeUpTime_, maxSpinSpeed_) {
		this->pBrain->pushState(*this);
	}
	virtual void cleanUp() {

	}
	virtual void executeBehavior() {
		// Update time
		this->passedTime += Locator::getGameTime()->getDeltaTime();
		
		// Rotate faster (But remember we've already rotated for 5 seconds!)
		currentSpinSpeed = maxSpinSpeed * ((this->passedTime + this->chargeUpTime) / chargeUpTime);
		this->rotate(currentSpinSpeed);

		// If we're still not colliding with the walls || some paddingtime prevents it from deadlocking itself
		if (this->inOrOutPRIVATE() || passedTime < paddingTime) {
			// Keep moving straight forward!
			this->pBrain->pushCommand(AICOMMANDS::MOVE);	
		}
		else {
			passedTime = 0;

			// STOP MOVING!
			this->pHead->setKineticVector(XMFLOAT3(0, 0, 0));

			// Stop rotating since we need to channel again
			this->rotate(0);

			// Pop back into channeling state
			this->pBrain->popState();
		}
	}
};


#endif
