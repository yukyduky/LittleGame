#include "EnemyMovingState.h"
#include "EnemyAttackingState.h"
#include "AIComponent.h"
#include "EnemyObject.h"
#include "Spell.h"

EnemyMovingState::EnemyMovingState(EnemyObject & pHead, AIComponent & pBrain) : EnemyState(pHead, pBrain)
{
	// Activate this state
	this->pBrain->pushState(*this);
}

void EnemyMovingState::cleanUp()
{

}

void EnemyMovingState::executeBehavior()
{
	/// Move towards the player
	XMFLOAT2 vectorToPlayer = this->pHead->getVectorToPlayer();

	// Set SimulatedMovement & Direction
	this->pBrain->SETsimulatedMovement(vectorToPlayer);
	this->pHead->setDirection(XMFLOAT3(vectorToPlayer.x, 0, vectorToPlayer.y));

	// If we're in range, switch state to attacking!
	if (this->pHead->getDistanceToPlayer() < this->attackRange) {

		// Cooldown is checked internally
		this->pBrain->pushCommand(AICOMMANDS::ATTACK);
	}

	// Move!
	this->pBrain->pushCommand(AICOMMANDS::MOVE);
}