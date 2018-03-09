#include "BossGeneratorBattleState.h"
#include "BossBattleIntroState.h"
#include "AIComponent.h"
#include "GamePlayState.h"

BossGeneratorBattleState::BossGeneratorBattleState(EnemyObject & pHead, AIComponent & pBrain, GamePlayState & pGPS, float bossScale)
	: BossState(pHead, pBrain, pGPS, bossScale)
{
	this->pBrain->pushState(*this);
	this->pHead->turnOnInvulnerability();
	this->phase = GENERATORBATTLEPHASE::FIRST;
	this->grid = &this->pGPS->GETgrid();
	this->numHorizontalSquares = ARENADATA::GETarenaWidth() / ARENADATA::GETsquareSize();
	this->numVerticalSquares = ARENADATA::GETarenaHeight() / ARENADATA::GETsquareSize();
	this->teleported = false;
	this->generatorsSpawned = false;
	this->counter = 0.0f;

}

void BossGeneratorBattleState::executeBehavior()
{
	XMFLOAT3 bossPosition = this->pHead->GETPosition();

	switch (this->phase) 
	{
	case GENERATORBATTLEPHASE::FIRST:
		// Prepare the fight by teleporting the player to the left side of the arena and the 
		// boss to the top middle part of the arena.
		if ((*this->grid)[0][0].state != TILESTATE::TTELEPORT && (*this->grid)[0][0].state != TILESTATE::TELEPORT) {
			for (int i = 0; i < this->numHorizontalSquares; i++) {
				for (int j = 0; j < this->numVerticalSquares; j++) {
					(*this->grid)[i][j].state = TILESTATE::TTELEPORT;
				}
			}
			this->pHead->setPosition(XMFLOAT3(ARENADATA::GETarenaWidth() * 0.5f, bossPosition.y, ARENADATA::GETarenaHeight() - this->bossScale));
		}
		// Spawn four generators that the player will have to destroy to be able to damage the boss
		if ((*this->grid)[0][0].state == TILESTATE::TELEPORT && !this->teleported) {
			this->teleported = true;
		}
		else if (this->teleported) {
			for (int i = 0; i < this->numHorizontalSquares; i++) {
				for (int j = 0; j < this->numVerticalSquares; j++) {
					(*this->grid)[i][j].state = TILESTATE::ACTIVE;
				}
			}
			this->phase = GENERATORBATTLEPHASE::ENEMYWAVESPHASE;
		}
		break;
	case GENERATORBATTLEPHASE::ENEMYWAVESPHASE:
		if (!this->generatorsSpawned) {
			this->pGPS->spawnBossGenerators();
			this->generatorsSpawned = true;
		}
		else {
			if (this->pGPS->checkGenerators()) {
				this->pHead->turnOffInvulnerability();
				this->phase = GENERATORBATTLEPHASE::DAMAGEBOSSPHASE;
				this->generatorsSpawned = false;
			}
			else {

			}
		}
		break;
	case GENERATORBATTLEPHASE::DAMAGEBOSSPHASE:
		this->counter += Locator::getGameTime()->getDeltaTime();
		if (this->counter >= 4.0f) {
			this->pHead->turnOnInvulnerability();
			this->phase = GENERATORBATTLEPHASE::ENEMYWAVESPHASE;
			this->counter = 0.0f;
		}
		break;

	}
}
