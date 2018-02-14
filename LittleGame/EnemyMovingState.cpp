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
	// If we're in range, switch state to attacking!
	if (this->pHead->getDistanceToPlayer() < this->attackRange) {
		// Push the attacking state
		this->pHead->setState(OBJECTSTATE::TYPE::ATTACKING);
		this->pBrain->pushState(*this->attackingStateTemplate);
		this->pBrain->pushCommand(AICOMMANDS::ATTACK);
	}
	else {
		// Move!
		this->pBrain->pushCommand(AICOMMANDS::MOVE);
	}	
}