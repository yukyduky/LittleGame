#pragma once
#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "ActorObject.h"
#include "GameObject.h"


class EnemyObject : public ActorObject
{
private:
	// attackComponent

public:
	EnemyObject(const size_t ID, float speed, XMFLOAT3 pos, XMFLOAT3 velocity, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType);

	virtual void update();
	virtual void attack() = 0;
};





#endif
