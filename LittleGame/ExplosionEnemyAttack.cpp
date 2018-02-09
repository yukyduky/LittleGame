#include "ExplosionEnemyAttack.h"



ExplosionEnemyAttack::ExplosionEnemyAttack(ActorObject& pHead)
{
	this->pHead = &pHead;
	pHead.addComponent(this);
}

const size_t ExplosionEnemyAttack::getID()
{
	return this->pHead->getID();
}
void ExplosionEnemyAttack::receive(GameObject & obj, Message msg)
{

}
void ExplosionEnemyAttack::update()
{

}
void ExplosionEnemyAttack::cleanUp()
{

}
void ExplosionEnemyAttack::attack()
{
	// Needs to know tiles around it, or act on an area around it.
}