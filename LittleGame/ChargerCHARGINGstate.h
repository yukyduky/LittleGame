#pragma once
#ifndef CHARGERCHARGINGSTATE_H
#define CHARGERCHARGINGSTATE_H

#include "ChargerState.h"

class ChargerChargingState : public ChargerState
{
public:
	ChargerChargingState(EnemyObject& pHead, AIComponent& pBrain) : ChargerState(pHead, pBrain) {
		this->pBrain->pushState(*this);
	}
	virtual void cleanUp() {

	}
	virtual void executeBehavior() {
		// If we're still not colliding with the walls
		if (this->inOrOut()) {
			// Keep moving straight forward!
			this->pBrain->pushCommand(AICOMMANDS::MOVE);	
		}
		else {
			// this->setRotation(originalRotation);
			// Pop back to ChargerChannelingState
			this->pBrain->popState();
		}
	}
};


#endif
