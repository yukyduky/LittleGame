#include "ImmolationEnemyAttack.h"
#include "ActorObject.h"
#include "EnemyObject.h"
#include "GamePlayState.h"

ImmolationEnemyAttack::ImmolationEnemyAttack(
	float damage, float attackDuration, float attackRange, 
	EnemyObject& pHead
)
{
	/*
	WARNING: THIS CLASS IS NOT MEANT TO BE SET OTHER COMPONENTS USUALLY ARE,
	IT INSTEAD IS SET ONTO AN ENEMYSTATE WHICH DEALS WITH IT.
	*/
	// Set up pointers
	this->pHead = &pHead;
	this->players = pHead.getPlayers();

	// this data might be given as input parameters if we want different kinds of immolation attackers
	this->damage = damage;
	this->attackDuration = attackDuration;
	this->attackRange = attackRange;
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

}
void ImmolationEnemyAttack::cleanUp()
{

}
void ImmolationEnemyAttack::attack()
{
	// Only coded to work against 1 player atm!
	(*this->players)[0]->dealDmg(this->damage);
}