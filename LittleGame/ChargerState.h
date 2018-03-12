#pragma once
#ifndef CHARGERSTATE_H
#define CHARGERSTATE_H

#include "EnemyState.h"

class ChargerState : public EnemyState
{
protected:
	bool inOrOut() {
		XMFLOAT3 position = this->pHead->GETPosition();
		bool result = false;
		int margin = 0;

		if ((position.x > margin) && (position.x < ARENADATA::GETarenaWidth() - margin)) {
			if ((position.z > margin) && (position.z < ARENADATA::GETarenaHeight() - margin)) {
				result = true;
			}
		}

		return result;
	}
	bool inOrOutPlus()
	{
		XMFLOAT3 position = this->pHead->GETPosition();
		bool result = false;
		int margin = ARENADATA::GETlengthOfWall() * ARENADATA::GETsquareSize() + 1;

		if ((position.x > margin) && (position.x < ARENADATA::GETarenaWidth() - margin)) {
			if ((position.z > margin) && (position.z < ARENADATA::GETarenaHeight() - margin)) {
				result = true;
			}
		}

		return result;
	}

public:
	ChargerState(EnemyObject& pHead, AIComponent& pBrain) : EnemyState(pHead, pBrain) {

	}
	virtual void cleanUp() {

	}
	virtual void executeBehavior() {

	}
};

#endif
