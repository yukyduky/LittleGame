#include "EnemyMovingState.h"
#include "EnemyAttackingState.h"
#include "AIComponent.h"
#include "EnemyObject.h"

EnemyMovingState::EnemyMovingState(EnemyObject & pHead, AIComponent & pBrain, EnemyAttackingState& attackState)
{
	// Set up pointers
	this->pHead = &pHead;
	this->pBrain = &pBrain;
	this->attackingStateTemplate = &attackState;

	// Misc
	this->attackRange = this->attackingStateTemplate->GETattackRange();
	
	// Activate this state
	this->pBrain->pushState(*this);
}

void EnemyMovingState::executeBehavior()
{
	// Update Movement
	this->pBrain->SETsimulatedMovement(this->pHead->getVectorToPlayer());

	// If we're in range, switch state to attacking!
	if (this->pHead->getDistanceToPlayer() < this->attackRange) {
		// Push the attacking state
		//this->pHead->setState(OBJECTSTATE::TYPE::ATTACKING);		-- Immolation shouldn't have an attackingState, since it has no delay when attacking
		//this->pBrain->pushState(*this->attackingStateTemplate);	-- //Shellow
		this->pBrain->pushCommand(AICOMMANDS::ATTACK);
	}

	// Move!
	this->pBrain->pushCommand(AICOMMANDS::MOVE);
}