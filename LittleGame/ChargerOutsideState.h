#pragma once
#ifndef CHARGEROUTSIDESTATE_H
#define CHARGEROUTSIDESTATE_H

#include "ChargerState.h"
#include <DirectXmath.h>
#include "AIComponent.h"
#include "EnemyObject.h"
#include "ChargerChannelingState.h"
using namespace DirectX;

class ChargerOutsideState : public ChargerState
{
private:
	XMFLOAT3 openingInTheArena = { 0, 0, 0.01 };

protected:
	
public:
	ChargerOutsideState(EnemyObject& pHead, AIComponent& pBrain, XMFLOAT3 openingInTheArena_, float chargeUpTime_, float maxSpinSpeed_, float collisionDamage_)
		: ChargerState(pHead, pBrain, chargeUpTime_, maxSpinSpeed_) {
		// Set values
		this->pBrain->pushState(*this);
		this->openingInTheArena = openingInTheArena_;
		this->pHead->setCollisionDamage(collisionDamage_);
	}
	virtual void cleanUp() {

	}
	virtual void executeBehavior() {
		/// Move inside the grid (move towards the player)
		XMFLOAT2 vectorToOpening;
		XMFLOAT3 myPos3 = this->pHead->GETPosition();
		vectorToOpening.x = openingInTheArena.x - myPos3.x;
		vectorToOpening.y = openingInTheArena.z - myPos3.z;

		// Normalize
		XMVECTOR tempMath = DirectX::XMLoadFloat2(&vectorToOpening);
		tempMath = DirectX::XMVector2Normalize(tempMath);
		DirectX::XMStoreFloat2(&vectorToOpening, tempMath);

		// Set SimulatedMovement & Direction
		this->pBrain->SETsimulatedMovement(vectorToOpening);
		this->pHead->setDirection(XMFLOAT3(vectorToOpening.x, 0, vectorToOpening.y));

		// Move!
		this->pBrain->pushCommand(AICOMMANDS::MOVE);

		// If we've come inside the arena, switch to the channeling state and let it solve the rest
		if (this->inOrOut()) {
			this->pHead->setKineticVector(XMFLOAT3(0, 0, 0));
			EnemyState* nextState = new ChargerChannelingState(*this->pHead, *this->pBrain, this->chargeUpTime, this->maxSpinSpeed);
		}
	}
};



#endif