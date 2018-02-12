#include "ImmolationEnemyAttack.h"
#include "ActorObject.h"
#include "EnemyObject.h"
#include "GamePlayState.h"

ImmolationEnemyAttack::ImmolationEnemyAttack(EnemyObject& pHead, std::vector<ActorObject*>* players)
{
	// Set up heads
	this->pHead = &pHead;
	pHead.addComponent(this);
	this->pHead2 = dynamic_cast<EnemyObject*>(&pHead);
	this->pHead2->SETattackComponent(this);
	this->players = players;

	// this data might be given through constructor if we want different kinds of immolation
	this->damage = 20;
	this->attackDuration = 0.1;
	this->attackRange = 100;
}

const size_t ImmolationEnemyAttack::getID()
{
	return this->pHead->getID();
}
void ImmolationEnemyAttack::receive(GameObject & obj, Message msg)
{

}
void ImmolationEnemyAttack::update()
{
	if (this->pHead2->getDistanceToPlayer() < this->attackRange) {
		this->attack();
	}
}
void ImmolationEnemyAttack::cleanUp()
{

}
void ImmolationEnemyAttack::attack()
{
	this->pHead->setState(OBJECTSTATE::TYPE::ATTACKING);

	// Only coded to work against 1 player atm!
	(*this->players)[0]->dealDmg(this->damage);
}