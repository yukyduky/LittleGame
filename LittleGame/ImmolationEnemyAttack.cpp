#include "ImmolationEnemyAttack.h"
#include "ActorObject.h"
#include "EnemyObject.h"
#include "GamePlayState.h"

ImmolationEnemyAttack::ImmolationEnemyAttack(
	float damage, float attackDuration, float attackRange, 
	EnemyObject& pHead
)
{
	// Set up pointers
	this->pHead = &pHead;
	pHead.addComponent(this);
	pHead.SETattackComponent(this);
	this->players = pHead.getPlayers();

	// this data might be given as input parameters if we want different kinds of immolation attackers
	this->attackDamage = damage;
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
	char msgbuf[20];

	// Only coded to work against 1 player atm!
	(*this->players)[0]->dealDmg(this->attackDamage);

	sprintf_s(msgbuf, "HEALTH: %f\n", (*this->players)[0]->GEThp());
	OutputDebugStringA(msgbuf);
}