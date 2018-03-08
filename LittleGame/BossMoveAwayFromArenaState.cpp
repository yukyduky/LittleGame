#include "BossMoveAwayFromArenaState.h"
#include "BossMoveToArenaState.h"
#include "AIComponent.h"

BossMoveAwayFromArenaState::BossMoveAwayFromArenaState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale) 
	: BossState(pHead, pBrain, pGPS, bossScale)
{
	this->pBrain->pushState(*this);
	this->pHead->turnOnInvulnerability();
}

void BossMoveAwayFromArenaState::executeBehavior() {
	// Move away from the arena
	XMFLOAT2 vectorAwayFromArena = XMFLOAT2(1.0f, 0.0f);
	// Set SimulatedMovement & Direction
	this->pBrain->SETsimulatedMovement(vectorAwayFromArena);
	this->pHead->setDirection(XMFLOAT3(vectorAwayFromArena.x, 0.0f, vectorAwayFromArena.y));

	// Move
	this->pBrain->pushCommand(AICOMMANDS::MOVE);
	// If we have moved far enough away from the arena, change state.
	if (this->pHead->GETPosition().x >= ARENADATA::GETarenaWidth() + 1000.0f) {
		this->changeState();
	}
}


void BossMoveAwayFromArenaState::changeState()
{
	XMFLOAT3 bossPos = this->pHead->GETPosition();
	this->pHead->setPosition(XMFLOAT3(ARENADATA::GETarenaWidth() + 1000.0f, bossPos.y, ARENADATA::GETarenaHeight() * 0.5f));
	EnemyState* bossMoveToArenaState = new BossMoveToArenaState(
		*this->pHead, *this->pBrain, *this->pGPS, this->bossScale
	);
}