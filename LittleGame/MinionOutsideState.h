#pragma once
#ifndef MINIONOUTSIDESTATE_H
#define MINIONOUTSIDESTATE_H

#include "SwarmerState.h"
#include "EnemyObject.h"
#include "AIComponent.h"
#include "SwarmerSeekingState.h"

class MinionOutsideState : public EnemyState
{
private:
	XMFLOAT3 openingInTheArena = { 0, 0, 0.01 };

	bool inOrOutPlus()
	{
		XMFLOAT3 position = this->pHead->GETPosition();
		bool result = false;
		int margin = 0;// ARENADATA::GETlengthOfWall() + ARENADATA::GETsquareSize() * 3;

		if ((position.x > margin) && (position.x < ARENADATA::GETarenaWidth() - margin)) {
			if ((position.z > margin) && (position.z < ARENADATA::GETarenaHeight() - margin)) {
				result = true;
			}
		}

		return result;
	}

public:
	MinionOutsideState(EnemyObject& pHead, AIComponent& pBrain, XMFLOAT3 openingInTheArena_)
		: EnemyState(pHead, pBrain)
	{
		this->openingInTheArena = openingInTheArena_;
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

		// Normalize
		XMVECTOR tempMath = DirectX::XMLoadFloat2(&vectorToOpening);
		tempMath = DirectX::XMVector2Normalize(tempMath);
		DirectX::XMStoreFloat2(&vectorToOpening, tempMath);

		// Set SimulatedMovement & Direction
		this->pBrain->SETsimulatedMovement(vectorToOpening);
		this->pHead->setDirection(XMFLOAT3(vectorToOpening.x, 0, vectorToOpening.y));

		// Move!
		this->pBrain->pushCommand(AICOMMANDS::MOVE);

		// If we've come inside the grid, ACT LIKE IT.
		if (this->inOrOutPlus()) {
			EnemyState* seekingState = new EnemyMovingState(*this->pHead, *this->pBrain);
		}
	}
};

#endif
