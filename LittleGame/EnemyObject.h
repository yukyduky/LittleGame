#pragma once
#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include "ActorObject.h"

class EnemyObject : public ActorObject
{
private:


public:
	EnemyObject(const size_t ID, float speed, XMFLOAT3 pos, XMFLOAT3 velocity, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType);

	virtual void update();
//	virtual void attack();
};





#endif
