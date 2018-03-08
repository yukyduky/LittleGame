#include "BossMoveToArenaState.h"
#include "BossBattleIntroState.h"
#include "AIComponent.h"


BossMoveToArenaState::BossMoveToArenaState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale) 
		: BossState(pHead, pBrain, pGPS, bossScale) 
{
	this->pBrain->pushState(*this);
	this->pHead->turnOnInvulnerability();
}

void BossMoveToArenaState::cleanUp()
{

}

void BossMoveToArenaState::executeBehavior()
{
	/// Move to the arena
	XMFLOAT2 vectorToArena = XMFLOAT2(-1.0f, 0.0f);
	// Set SimulatedMovement & Direction
	this->pBrain->SETsimulatedMovement(vectorToArena);
	this->pHead->setDirection(XMFLOAT3(vectorToArena.x, 0.0f, vectorToArena.y));

	// Move!
	this->pBrain->pushCommand(AICOMMANDS::MOVE);
	XMFLOAT3 bossPos = this->pHead->GETPosition();
	// If we've reached the arena, change state.
	if (bossPos.x <= ARENADATA::GETarenaWidth()) {
		this->pHead->setPosition(XMFLOAT3(ARENADATA::GETarenaWidth(), bossPos.y, bossPos.z));
		EnemyState* bossBattleIntroState = new BossBattleIntroState(
			*this->pHead, *this->pBrain, *this->pGPS, this->bossScale
		);
	}
}