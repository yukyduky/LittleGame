#pragma once
#ifndef BOSSSTATE_H_
#define BOSSSTATE_H_

#include "EnemyState.h"
#include "EnemyObject.h"
#include "DirectXMath.h"


class BossState : public EnemyState
{
private:
	
protected:
	GamePlayState* pGPS;
	float bossScale;

public:
	BossState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale) : EnemyState(pHead, pBrain) 
	{
		this->pGPS = &pGPS;
		this->bossScale = bossScale;
	}
	virtual void executeBehavior() = 0;

};

#endif // !BOSSINTROSTATE_H_