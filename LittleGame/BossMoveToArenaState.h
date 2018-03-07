#pragma once
#ifndef BOSSMOVETOARENASTATE_H_
#define BOSSMOVETOARENASTATE_H_

#include "BossState.h"
#include "AIComponent.h"
#include "BossBattleIntroState.h"

class BossMoveToArenaState : public BossState
{
private:

public:
	BossMoveToArenaState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale) : BossState(pHead, pBrain, pGPS, bossScale)
	{
		this->pBrain->pushState(*this);
	}

	void executeBehavior() {
		/// Move to the arena
		XMFLOAT2 vectorToArena = XMFLOAT2(-1.0f, 0.0f);
		// Set SimulatedMovement & Direction
		this->pBrain->SETsimulatedMovement(vectorToArena);
		this->pHead->setDirection(XMFLOAT3(vectorToArena.x, 0.0f, vectorToArena.y));

		// Move!
		this->pBrain->pushCommand(AICOMMANDS::MOVE);
		XMFLOAT3 bossPos = this->pHead->GETPosition();
		// If we've reached the arena, change state.
		if (bossPos.x <= ARENADATA::GETarenaWidth() * 0.5f) {
			this->pHead->setPosition(XMFLOAT3(ARENADATA::GETarenaWidth() * 0.5f, bossPos.y, bossPos.z));
			EnemyState* bossBattleIntroState = new BossBattleIntroState(
				*this->pHead, *this->pBrain, *this->pGPS, this->bossScale
			);
		}
	}

};

#endif // !BOSSINTROSTATE_H_
