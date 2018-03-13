#pragma once
#ifndef CHARGERSTATE_H
#define CHARGERSTATE_H

#include "EnemyState.h"

class ChargerState : public EnemyState
{
protected:
	float passedTime = 0.0f;
	float chargeUpTime = 5.0f;
	float maxSpinSpeed = 60.0f; // Radians
	float currentSpinSpeed = maxSpinSpeed;

	void rotate(float spinSpeed) {
		// Affect rotation
		XMFLOAT3 axis = { 0, 1, 0 };
		XMVECTOR vecAxis;
		vecAxis = DirectX::XMLoadFloat3(&axis);
		XMMATRIX rotationMatrix = DirectX::XMMatrixRotationAxis(vecAxis, spinSpeed);
		this->pHead->SETrotationMatrix(rotationMatrix);
	}
	// Loosely checks if your inside
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
	// Checks if ur inside with margin
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
	ChargerState(EnemyObject& pHead, AIComponent& pBrain, float chargeUpTime_, float maxSpinSpeed_) : EnemyState(pHead, pBrain) {
		this->chargeUpTime = chargeUpTime_;
		this->maxSpinSpeed = maxSpinSpeed_;
	}
	virtual void cleanUp() = 0;
	virtual void executeBehavior() = 0;
};

#endif
