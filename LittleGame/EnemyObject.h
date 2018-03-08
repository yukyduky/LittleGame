#pragma once
#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "ActorObject.h"
#include "GameObject.h"
#include "EnemyAttackComponent.h"
#include "EnemyState.h"


class EnemyMovingState;

class EnemyObject : public ActorObject
{
private:
	EnemyAttackComponent * attackComponent = nullptr;
	std::vector<ActorObject*>* players = nullptr;
	// Same vector as the one which relies in this, soon-to-be, AI-component
	std::vector<EnemyState*> states;

	// Almost normalized
	XMFLOAT2 normalizedVectorToPlayer;
	float distanceToPlayer = 0.0f;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Updates internal 'normalizedVectorToPlayer' and 'distanceToPlayer'
	*/
	void updateRelationsToPlayer(XMFLOAT2 myPos, XMFLOAT2 playerPos);

	

public:
	EnemyObject(const size_t ID, float accelerationSpeed, float topSpeed, XMFLOAT3 pos, GamePlayState* pGPS, std::vector<ActorObject*>* players, OBJECTTYPE::TYPE objectType);

	void SETattackComponent(EnemyAttackComponent* attackComponent);

	XMFLOAT2 getVectorToPlayer();
	float getDistanceToPlayer();
	void dealDmgToPlayer(size_t playerID, float damage);
	std::vector<ActorObject*>* getPlayers();


	virtual void update();
	virtual void attack();
};


#endif
