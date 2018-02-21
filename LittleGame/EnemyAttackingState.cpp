#include "EnemyAttackingState.h"
#include "EnemyObject.h"


EnemyAttackingState::EnemyAttackingState(EnemyObject& pHead, AIComponent& pBrain, EnemyAttackComponent& attackComponent)
{
	// Set up pointers
	this->pHead				= &pHead;
	this->pBrain			= &pBrain;
	this->attackComponent	= &attackComponent;

	// Misc
	this->attackDamage		= attackComponent.GETattackDamage();
	//this->attackDuration	= attackComponent.GETattackDuration();
	this->attackRange		= attackComponent.GETattackRange();
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
		this->pHead->setState(OBJECTSTATE::TYPE::ACTIVATED);
		this->pBrain->popState();
	}
	// If we wanted attacks to be more complex we simply use more states!
}

float EnemyAttackingState::GETattackDamage()
{
	return this->attackDamage;
}

float EnemyAttackingState::GETattackDuration()
{
	return this->attackDuration;
}

float EnemyAttackingState::GETattackRange()
{
	return this->attackRange;
}
