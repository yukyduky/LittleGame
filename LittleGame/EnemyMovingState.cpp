#include "EnemyMovingState.h"
#include "EnemyAttackingState.h"
#include "AIComponent.h"
#include "EnemyObject.h"
#include "Spell.h"

EnemyMovingState::EnemyMovingState(EnemyObject & pHead, AIComponent & pBrain, EnemyAttackingState& attackState)
{
	// Set up pointers
	this->pHead = &pHead;
	this->pBrain = &pBrain;
	this->attackingStateTemplate = &attackState;

	// Misc
	this->attackRange = this->pHead->getFirstSpell()->getAggroRange();
	
	// Activate this state
	this->pBrain->pushState(*this);
}

void EnemyMovingState::executeBehavior()
{
	// Update Direction/Movement (same thing but spells needs generic 'getDirection()')
	XMFLOAT2 vectorToPlayer = this->pHead->getVectorToPlayer();
	this->pBrain->SETsimulatedMovement(vectorToPlayer);
	XMFLOAT3 temp;						// XMFLOAT2
	temp.x = vectorToPlayer.x;			//	 to
	temp.y = 0;							// XMFLOAT3
	temp.z = vectorToPlayer.y;
	this->pHead->setDirection(temp);

	// If we're in range, switch state to attacking!
	if (this->pHead->getDistanceToPlayer() < this->attackRange) {

		// Cooldown is checked internally
		this->pBrain->pushCommand(AICOMMANDS::ATTACK);
	}

	// Move!
	this->pBrain->pushCommand(AICOMMANDS::MOVE);
}