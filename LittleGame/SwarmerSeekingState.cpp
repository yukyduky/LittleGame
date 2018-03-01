#include "SwarmerSeekingState.h"
#include "AIComponent.h"
#include "EnemyObject.h"
#include "SwarmerState.h"

SwarmerSeekingState::SwarmerSeekingState(
	EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID
) : SwarmerState(pHead, pBrain, pGrid_, swarmerID)
{
	// Activate this state
	this->pBrain->pushState(*this);
}

void SwarmerSeekingState::executeBehavior()
{
	/// Move towards the seekPosition
	XMFLOAT3 seekPosition = this->getPositionToSeek();
	XMFLOAT3 myPosition = this->pHead->GETPosition();
	XMFLOAT3 newDirection;
	newDirection.x = seekPosition.x - myPosition.x;
	newDirection.y = seekPosition.y - myPosition.y;
	newDirection.z = seekPosition.z - myPosition.z;

	// Convert for optimization
	XMVECTOR vecDirection = DirectX::XMLoadFloat3(&newDirection);
	vecDirection = DirectX::XMVector3Normalize(vecDirection);
	DirectX::XMStoreFloat3(&newDirection, vecDirection);


	/// Shoot a spell (spells handle their own cooldown)
	if (this->pHead->getDistanceToPlayer() < this->attackRange) {
		// Cooldown is checked internally
		this->pBrain->pushCommand(AICOMMANDS::ATTACK);
	}

	// Set SimulatedMovement & Direction
	this->pBrain->SETsimulatedMovement(XMFLOAT2(newDirection.x, newDirection.z));
	this->pHead->setDirection(newDirection);

	// Do the 'manet-shooting'
//	this->adjustAim();

	// Adjust velocity based on pulsing
	this->pulse();

	// Move!
	this->pBrain->pushCommand(AICOMMANDS::MOVE);
}