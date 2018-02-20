#include "SwarmerEnemyAttack.h"
#include "EnemyAttackComponent.h"
#include "ActorObject.h"
#include "EnemyObject.h"

SwarmerEnemyAttack::SwarmerEnemyAttack(EnemyObject& pHead, int& activeEnemiesCount, float projectileDamage, float projectileDuration, float projectileRange)
{
	// Set up pointers
	this->pHead = &pHead;
	pHead.addComponent(this);
	pHead.SETattackComponent(this);
	this->players = pHead.getPlayers();
	this->pActiveEnemiesCount = pActiveEnemiesCount;

	// this data might be given as input parameters if we want different kinds of immolation attackers
	this->attackDamage = projectileDamage;
	this->attackDuration = projectileDuration;
	this->attackRange = projectileRange;
}


const size_t SwarmerEnemyAttack::getID()
{
	return this->pHead->getID();
}
void SwarmerEnemyAttack::receive(GameObject & obj, Message msg)
{

}
void SwarmerEnemyAttack::update()
{

}
void SwarmerEnemyAttack::cleanUp()
{
	// The object this is attached to is getting cleaned, which means, IT'S DEAD.
	(*this->pActiveEnemiesCount)--;

}
void SwarmerEnemyAttack::attack()
{
	//char msgbuf[20];

	//// Only coded to work against 1 player atm!
	//(*this->players)[0]->dealDmg(this->attackDamage);

	//sprintf_s(msgbuf, "HEALTH: %f\n", (*this->players)[0]->GEThp());
	//OutputDebugStringA(msgbuf);
}