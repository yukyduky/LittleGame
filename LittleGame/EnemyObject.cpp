#include "EnemyObject.h"
#include "Locator.h"
#include "CollisionHandler.h"
#include "EnemyMovingState.h"
#include "EnemyState.h"
#include "GameObject.h"
#include "Spell.h"

//#define DISTANCE_FACTOR 1.4142135623730950488016887242097	// Fetched from CollisionHandler.h

void EnemyObject::updateRelationsToPlayer(XMFLOAT2 myPos, XMFLOAT2 playerPos)
{
	// This method calculates the approximate distance between two points.
	// NOTE: It does NOT use the 'sqrt()' function resulting in optimization!
	float xDiff = std::abs(playerPos.x - myPos.x);
	float yDiff = std::abs(playerPos.y - myPos.y);
	float minDiff = std::_Min_value(xDiff, yDiff);

	this->distanceToPlayer = (minDiff * DISTANCE_FACTOR);
	this->distanceToPlayer += ((xDiff - minDiff) + (yDiff - minDiff));

	this->normalizedVectorToPlayer = playerPos - myPos;
	float optimization = 1 / this->distanceToPlayer;
	this->normalizedVectorToPlayer.x *= optimization;
	this->normalizedVectorToPlayer.y *= optimization;
}



EnemyObject::EnemyObject(const size_t ID, float velocityMagnitude, float topSpeed, XMFLOAT3 pos, GamePlayState* pGPS, std::vector<ActorObject*>* players, OBJECTTYPE::TYPE objectType, float hp_in)
	: ActorObject(ID, velocityMagnitude, topSpeed, pos, pGPS, objectType, hp_in)
{
	this->enemyType = enemyType;
	this->players = players;
}

void EnemyObject::setIfCharged(bool isItACharger)
{
	this->charged = isItACharger;
}

void EnemyObject::SETattackComponent(EnemyAttackComponent* attackComponent)
{
	this->attackComponent = attackComponent;
}

EnemyAttackComponent * EnemyObject::GETattackComponent()
{
	return this->attackComponent;
}

bool EnemyObject::getIfCharged()
{
	return this->charged;
}

void EnemyObject::setCollisionDamage(float collisionDamage_)
{
	this->collisionDamage = collisionDamage_;
}

float EnemyObject::getCollisionDamage()
{
	return this->collisionDamage;
}

XMFLOAT2 EnemyObject::getVectorToPlayer()
{
	return this->normalizedVectorToPlayer;
}

float EnemyObject::getDistanceToPlayer()
{
	return this->distanceToPlayer;
}

void EnemyObject::dealDmgToPlayer(size_t playerID, float damage)
{
	(*this->players)[playerID]->dealDmg(damage);
}

std::vector<ActorObject*>* EnemyObject::getPlayers()
{
	return this->players;
}

ENEMYTYPE::TYPE EnemyObject::getEnemyType()
{
	return this->enemyType;
}

void EnemyObject::update()
{
	// Find out where you are in relation to the player.
	XMFLOAT3 playerPos = (*players)[0]->GETPosition();
	this->updateRelationsToPlayer(XMFLOAT2(this->pos.x, this->pos.z), XMFLOAT2(playerPos.x, playerPos.z));
	this->move();

	switch (this->state)
	{
	case OBJECTSTATE::TYPE::ACTIVATED:
		// Act according to current state
		for (auto &component : this->components) {
			component->update();
		}
		break;
	case OBJECTSTATE::TYPE::BOSSSUBMERGE:
		if (this->pos.y > -300.0f) {
			this->pos.y -= 3.0f;
			this->updateWorldMatrix();
		}
		else {
			this->pos.y = -300.0f;
			this->state = OBJECTSTATE::TYPE::ACTIVATED;
		}
		break;
	case OBJECTSTATE::TYPE::BOSSEMERGE:
		if (this->pos.y < 50.0f) {
			this->pos.y += 3.0f;
			this->updateWorldMatrix();
		}
		else {
			this->pos.y = 50.0f;
			this->state = OBJECTSTATE::TYPE::ACTIVATED;
			this->turnOffInvulnerability();
		}
		break;
	default:
		break;
	}
	
	// Also update the cooldown on spells
	if (this->spells.size() > 0) {
		this->spells[0]->update();
	}
		
}

void EnemyObject::attack()
{
//	this->attackComponent->attack();
	this->spells[0]->castSpell();
}

void EnemyObject::bossAttack01()
{
	this->spells[0]->castSpell();
}

void EnemyObject::bossAttack02()
{
	this->spells[1]->castSpell();
}

void EnemyObject::bossAttack03()
{
	this->spells[2]->castSpell();
}

void EnemyObject::setHp(float hp)
{
	this->hp = hp;
}
