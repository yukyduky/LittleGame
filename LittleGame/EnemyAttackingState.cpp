#include "EnemyAttackingState.h"
#include "EnemyObject.h"


EnemyAttackingState::EnemyAttackingState(EnemyObject& pHead, AIComponent& pBrain, EnemyAttackComponent& attackComponent)
{
	this->pHead = &pHead;
	this->pBrain = &pBrain;
	this->attackComponent = &attackComponent;
}

void EnemyAttackingState::attack()
{
	this->attackComponent->attack();
}

void EnemyAttackingState::executeBehavior()
{
	// We're currently waiting for the attack so be over, so check on it!
	if (this->attackComponent->timeToAttack() == true) {
		// Attack is over, pop this state and get back to moving
		this->pBrain->popState();
	}
	// If we wanted attacks to be more complex we simply use more states!
}