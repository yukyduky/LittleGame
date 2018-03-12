#pragma once
#ifndef SWARMERSTATE_H
#define SWARMERSTATE_H

#include "EnemyState.h"
#include "Grid.h"
#include "EnemyObject.h"
#include "DirectXMath.h"
#include "Spell.h"

class EnemyObject;

class SwarmerState : public EnemyState
{
private:
	// Originals are used so we can go back to the value after altering it depending on neighbours
	//
	size_t swarmerID = 0;
	Grid *pGrid = nullptr;
	float originalSpellCooldown = this->pHead->getFirstSpell()->getCoolDown();
	float spellCooldown = originalSpellCooldown;
	float passedTime = 0;
	float originalPulseInterval = 3.5;
	float pulseInterval = originalPulseInterval;
	float originalVelocity = this->pHead->GETvelocityMagnitude();
	float timeFactor = originalVelocity / pulseInterval;


	// Used to balance how much/little the swarmers want to avoid walls/player
	struct ScaredFactor {
		float playerMaxFearFactor = 320;
		float walls = 1;
	};
	ScaredFactor scaredFactor;

	float pulseFormula(float dt) {
		float returnValue = (originalVelocity - timeFactor * dt);
		// Let's not even have the possibility of negative velocity
		if (returnValue > 0)
			return returnValue;
		else
			return 0;
	}

protected:
	bool timeToPulse = true;
	std::vector<EnemyObject*> neighbours;
	void adjustAim() {

		int degree = Locator::getRandomGenerator()->GenerateInt(-45, 45);
		XMFLOAT3 newDirection = this->pHead->getDirection();

		int radDegree = degree * DirectX::XM_PI / 180;

		newDirection.x += std::cos(radDegree);
		newDirection.z += std::sin(radDegree);
		this->pHead->setDirection(newDirection);
	}
	void pulse() {
		// Get time
		float dt = Locator::getGameTime()->getDeltaTime();
		this->passedTime += dt;

		// Adjust velocity based on time
		this->pHead->SETvelocityMagnitude(pulseFormula(this->passedTime));

		// Reset if necessary
		if (this->passedTime > pulseInterval) {
			this->passedTime = 0;
			this->timeToPulse = true;
		}
	}
	void updateNeighbours(DirectX::XMFLOAT2 position) {
		this->neighbours = this->pGrid->getNeighbours(position);
	}
	void setPulseInterval(float pulseInterval_) {
		this->pulseInterval = pulseInterval_;
	}
	void setSpellCooldown(float cooldown) {
		this->spellCooldown = cooldown;
	}
	float getOriginalSpellCooldown() {
		return this->originalSpellCooldown;
	}
	float getOriginalPulseInterval() {
		return this->originalPulseInterval;
	}
	float getOriginalVelocity() {
		return this->originalVelocity;
	}
	size_t getSwarmerID() {
		return this->swarmerID;
	}
	XMFLOAT3 getPositionToSeek() {
		return this->pGrid->getPositionToSeek();
	}
	// Returns Normalized
	XMFLOAT3 getDirectionToSeek() {
		XMFLOAT3 myPosition = this->pHead->GETPosition();
		XMFLOAT3 positionToSeek = this->getPositionToSeek();
		XMFLOAT3 directionToSeek = { 0, 0, 0.0001f };
		directionToSeek.x = positionToSeek.x - myPosition.x;
		directionToSeek.y = positionToSeek.y - myPosition.y;
		directionToSeek.z = positionToSeek.z - myPosition.z;

		XMVECTOR tempMath = DirectX::XMLoadFloat3(&directionToSeek);
		tempMath = DirectX::XMVector3Normalize(tempMath);
		DirectX::XMStoreFloat3(&directionToSeek, tempMath);

		return directionToSeek;
	}
	std::vector<EnemyObject*> getNeighbours() {
		XMFLOAT3 myPosition = this->pHead->GETPosition();
		return this->pGrid->getNeighbours(XMFLOAT2(myPosition.x, myPosition.z));
	}
	Grid* getGrid() {
		return this->pGrid;
	}
	// In = true | out = false
	bool inOrOut() {	
		XMFLOAT3 position = this->pHead->GETPosition();
		return this->pGrid->inOrOut(XMFLOAT2(position.x, position.z));
	}
	bool inOrOutPlus() {
		XMFLOAT3 position = this->pHead->GETPosition();
		return this->pGrid->inOrOutPLUS(XMFLOAT2(position.x, position.z));
	}
	// Returns Normalized
	XMFLOAT3 getDirectionToAveragePosition(std::vector<EnemyObject*> relevantEnemies) {
		XMFLOAT3 averagePosition = { 0, 0, 0.0001f };
		XMFLOAT3 averageDirection = { 0, 0, 0.0001f };
		XMFLOAT3 currentNeighbourPosition = { 0, 0, 0.0001f };
		XMFLOAT3 myPosition = { 0, 0, 0.0001f };

		for (auto &currentEnemy : relevantEnemies) {
			currentNeighbourPosition = currentEnemy->GETPosition();
			averagePosition.x += currentNeighbourPosition.x;
			averagePosition.y += currentNeighbourPosition.y;
			averagePosition.z += currentNeighbourPosition.z;
		}

		// We'd rather mutliply than divide
		float optimizer = 1.0 / relevantEnemies.size();
		averagePosition.x *= optimizer;
		averagePosition.y *= optimizer;
		averagePosition.z *= optimizer;

		averageDirection.x = averagePosition.x - myPosition.x;
		averageDirection.y = averagePosition.y - myPosition.y;
		averageDirection.z = averagePosition.z - myPosition.z;

		XMVECTOR tempMath = DirectX::XMLoadFloat3(&averageDirection);
		tempMath = DirectX::XMVector3Normalize(tempMath);
		DirectX::XMStoreFloat3(&averageDirection, tempMath);

		return averageDirection;
	}
	// Returns Normalized
	XMFLOAT3 wander() {
		float dt = Locator::getGameTime()->getDeltaTime();
		float rotationSpeed = 10;
		int randomX = Locator::getRandomGenerator()->GenerateInt(0, ARENADATA::GETarenaWidth()-ARENADATA::GETsquareSize());
		int randomY = Locator::getRandomGenerator()->GenerateInt(0, ARENADATA::GETarenaHeight()-ARENADATA::GETsquareSize());

		XMFLOAT2 seekPos;
		XMFLOAT2 desiredDirection;
		XMFLOAT2 steeringDirection;

		seekPos.x = randomX;
		seekPos.y = randomY;

		// Calculate desired direction
		desiredDirection.x = seekPos.x - this->pHead->GETPosition().x;
		desiredDirection.y = seekPos.y - this->pHead->GETPosition().z;

		// Normalize it
		XMVECTOR vecDesired = DirectX::XMLoadFloat2(&desiredDirection);
		vecDesired = XMVector2Normalize(vecDesired);
		DirectX::XMStoreFloat2(&desiredDirection, vecDesired);

		// Calculate the steering direction
		steeringDirection.x = desiredDirection.x - this->pBrain->GETnormalizedVectorOfLeftStick().x;
		steeringDirection.y = desiredDirection.y - this->pBrain->GETnormalizedVectorOfLeftStick().y;

		// Normalize it
		XMVECTOR vecSteering = DirectX::XMLoadFloat2(&steeringDirection);
		vecDesired = XMVector2Normalize(vecSteering);
		DirectX::XMStoreFloat2(&steeringDirection, vecSteering);

		// Affect the current direction
		XMFLOAT3 currentDirection = { 0, 0, 0.0001f };
		currentDirection.x = this->pBrain->GETnormalizedVectorOfLeftStick().x;
		currentDirection.z = this->pBrain->GETnormalizedVectorOfLeftStick().y;

		currentDirection.x += steeringDirection.x * rotationSpeed * dt;
		currentDirection.z += steeringDirection.y * rotationSpeed * dt;

		// Then normalize the current direction
		XMVECTOR vecDirection = DirectX::XMLoadFloat3(&currentDirection);
		vecDirection = XMVector3Normalize(vecDirection);
		DirectX::XMStoreFloat3(&currentDirection, vecDirection);

		return currentDirection;
	}
	// Returns Normalized*ProperlyScaled
	XMFLOAT3 avoidPlayer() {
		XMFLOAT3 playerPos = (*this->pHead->getPlayers())[0]->GETPosition();
		XMFLOAT3 myPos = this->pHead->GETPosition();
		XMFLOAT3 direction;
		XMFLOAT3 length;

		// Calculate the affecting direction
		direction.x = myPos.x - playerPos.x;
		direction.y = myPos.y - playerPos.y;
		direction.z = myPos.z - playerPos.z;

		// Find out the length
		XMVECTOR vecDirection = DirectX::XMLoadFloat3(&direction);
		vecDirection = XMVector3Length(vecDirection);
		DirectX::XMStoreFloat3(&length, vecDirection);

		// Normalize the direction so it's magnitude is only affected by fear
		vecDirection = DirectX::XMLoadFloat3(&direction);
		vecDirection = XMVector3Normalize(vecDirection);
		DirectX::XMStoreFloat3(&direction, vecDirection);

		// Balance it, lower length = higher fear and vice versa.
		if (length.x < 1) // The highest fear is reached at length 1 and cannot go towards infinity when denominator->0
			length.x = 1;
		float fear = this->scaredFactor.playerMaxFearFactor / length.x;

		// Affect its magnitude by how afraid it is of the player.
		direction.x *= fear;
		direction.y *= fear;
		direction.z *= fear;

		// Return it
		return direction;
	}
	// Returns Properly scaled
	XMFLOAT3 avoidWalls() {
		XMFLOAT3 myPos = this->pHead->GETPosition();
		return this->getGrid()->avoidWalls(myPos);

//		// ------------------------------------
//		XMFLOAT3 centerPos = { 0, 0, 0.0001f };
//		XMFLOAT3 myPos = this->pHead->GETPosition();
//		XMFLOAT3 direction = { 0, 0, 0.0001f };
//		centerPos.x = ARENADATA::GETarenaWidth() / 2;
//		centerPos.z = ARENADATA::GETarenaHeight() / 2;
//
//		// Calculate direction
//		direction.x = centerPos.x - myPos.x;
//		direction.y = centerPos.y - myPos.y;
//		direction.z = centerPos.z - myPos.z;
//
//		// Scale here somehow?
//		float denominator = (ARENADATA::GETarenaWidth() + ARENADATA::GETarenaHeight()) / 2;
//		float scale = 1.0 / denominator;
//		direction.x *= scale;
//		direction.y *= scale;
//		direction.z *= scale;
//
//		// Normalize
////		XMVECTOR tempMath = DirectX::XMLoadFloat(&direction.x);
////		tempMath = DirectX::XMVector3Normalize(tempMath);
////		DirectX::XMStoreFloat3(&direction, tempMath);
//		 
//		// Scale how? Based on what?
//		return direction;
	}

public:
	SwarmerState(EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID) : EnemyState(pHead, pBrain) {
		this->pGrid = pGrid_;
		this->swarmerID = swarmerID;
	}
	virtual void removeFromGrid() {
		if (this->pGrid->gridAlive()) {
			this->pGrid->removeSwarmer(this->swarmerID);
		}
	}
	virtual void executeBehavior() = 0;

};

#endif

