#include "EnemyState.h"
#include "EnemyObject.h"
#include "Spell.h"

EnemyState::EnemyState(EnemyObject& pHead, AIComponent& pBrain) {
	// Set up pointers
	this->pHead = &pHead;
	this->pBrain = &pBrain;
	// Set up other internal data.
	if (this->pHead->getFirstSpell() != nullptr) {
		this->attackRange = this->pHead->getFirstSpell()->getAttackRange();
	}
	else {
		this->attackRange = -1;
	}
}