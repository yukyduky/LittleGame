#pragma once
#ifndef BOSSSTATE_H_
#define BOSSSTATE_H_

#include "EnemyState.h"
#include "EnemyObject.h"
#include "DirectXMath.h"


class BossState : public EnemyState
{
private:
	size_t ID = 0;

protected:

public:
	BossState(EnemyObject& pHead, AIComponent& pBrain, size_t ID) : EnemyState(pHead, pBrain) {
		this->ID = ID;
	}


};

#endif // !BOSSINTROSTATE_H_