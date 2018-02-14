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

	switch (Locator::getRandomGenerator()->GenerateInt(1, 11)) {
	case 1: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_1);
		break;
	}
	case 2: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_2);
		break;
	}
	case 3: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_3);
		break;
	}
	case 4: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_4);
		break;
	}
	case 5: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_5);
		break;
	}
	case 6: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_6);
		break;
	}
	case 7: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_7);
		break;
	}
	case 8: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_8);
		break;
	}
	case 9: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_9);
		break;
	}
	case 10: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_10);
		break;
	}
	case 11: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_11);
		break;
	}
			 break;
	}

	switch (Locator::getRandomGenerator()->GenerateInt(1, 9)) {
	case 1: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_1);
		break;
	}
	case 2: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_2);
		break;
	}
	case 3: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_3);
		break;
	}
	case 4: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_4);
		break;
	}
	case 5: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_5);
		break;
	}
	case 6: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_6);
		break;
	}
	case 7: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_7);
		break;
	}
	case 8: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_8);
		break;
	}
	case 9: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_9);
		break;
	}
			break;
	}

	sprintf_s(msgbuf, "HEALTH: %f\n", (*this->players)[0]->GEThp());
	OutputDebugStringA(msgbuf);
}