#pragma once
#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "ActorObject.h"
#include "EnemyIncludes.h"

class ActorObject;
class EnemyState;
class EnemyMovingState;
class EnemyAttackComponent;
class AIComponent;



class EnemyObject : public ActorObject
{
private:
	ENEMYTYPE::TYPE enemyType = ENEMYTYPE::SIZE;
	EnemyAttackComponent * attackComponent = nullptr;
	AIComponent* pBrain = nullptr;
	std::vector<ActorObject*>* players = nullptr;

	// Almost normalized
	XMFLOAT2 normalizedVectorToPlayer;
	float distanceToPlayer = 0.0f;

	bool charged = false;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Updates internal 'normalizedVectorToPlayer' and 'distanceToPlayer'
	*/
	void updateRelationsToPlayer(XMFLOAT2 myPos, XMFLOAT2 playerPos);

public:
	EnemyObject(ENEMYTYPE::TYPE enemyType, size_t ID, XMFLOAT3 pos, float velocity, GamePlayState* pGPS, std::vector<ActorObject*>* players, OBJECTTYPE::TYPE objectType);

	void setIfCharged(bool isItACharger);
	void SETattackComponent(EnemyAttackComponent* attackComponent);
	EnemyAttackComponent* GETattackComponent();
	bool getIfCharged();

	XMFLOAT2 getVectorToPlayer();
	float getDistanceToPlayer();
	void dealDmgToPlayer(size_t playerID, float damage);
	std::vector<ActorObject*>* getPlayers();
	ENEMYTYPE::TYPE getEnemyType();

	virtual void update();
	virtual void attack();
	virtual void bossAttack01();
	virtual void bossAttack02();
	virtual void bossAttack03();

};


#endif
