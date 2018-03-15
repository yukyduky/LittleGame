#include "BossBattleIntroState.h"
#include "AIComponent.h"
#include "GamePlayState.h"
#include "BossMoveAwayFromArenaState.h"
#include "BossGeneratorBattleState.h"


void BossBattleIntroState::createNewWave()
{
	TeleportWave newWave;
	int openingIndexStepper = Locator::getRandomGenerator()->GenerateInt(-15, 15);
	int openingIndex = this->latestWaveOpeningIndex + openingIndexStepper;
	if (openingIndex < 3) {
		openingIndex = this->latestWaveOpeningIndex - openingIndexStepper;
	}
	else if (openingIndex > this->numSquareVertical - 4) {
		openingIndex = this->latestWaveOpeningIndex - openingIndexStepper;
	}
	this->latestWaveOpeningIndex = openingIndex;

	for (int i = 0; i < this->numSquareVertical; i++) {
		if (i != openingIndex && i
			!= openingIndex + 1 && i != openingIndex + 2 &&
			i != openingIndex - 1 && i != openingIndex - 2) {
			newWave.pattern.push_back(TILESTATE::TELEPORT);
		}
		else {
			newWave.pattern.push_back(TILESTATE::ACTIVE);
		}
	}
	newWave.currentIndexX = this->numSquareHorizontal - 7;
	this->waves.push_back(newWave);
}

BossBattleIntroState::BossBattleIntroState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale)
	: BossState(pHead, pBrain, pGPS, bossScale)
{
	this->pBrain->pushState(*this);
	this->grid = &this->pGPS->GETgrid();
	this->pHead->turnOnInvulnerability();
	this->numSquareHorizontal = ARENADATA::GETarenaWidth() / ARENADATA::GETsquareSize();
	this->numSquareVertical = ARENADATA::GETarenaHeight() / ARENADATA::GETsquareSize();
	this->waveIterations = 4;
	this->teleported = false;
	this->bossMaxHealth = this->pHead->GEThpMAX();
	this->latestWaveOpeningIndex = this->numSquareVertical / 2;

}

void BossBattleIntroState::cleanUp()
{
}

void BossBattleIntroState::executeBehavior()
{
	float dt = Locator::getGameTime()->getDeltaTime();
	int indexX = 0;
	int indexY = 0;
	if (this->bossMaxHealth * 0.66667 >= this->pHead->GEThp()) {
		EnemyState* bossGeneratorBattleState = new BossGeneratorBattleState(
			*this->pHead, *this->pBrain, *this->pGPS, this->bossScale
		);
	}
	else {
		switch (this->phase)
		{
		case INTROPHASE::FIRST:
			//Prepare the fight by teleporting the player to the left side of the arena
			//Also change state of the tiles infront of the boss that the player needs to reach
			// to make the boss vulnerable.
			for (int i = 0; i < this->numSquareHorizontal; i++) {
				for (int j = 0; j < this->numSquareVertical; j++) {
					(*this->grid)[i][j].state = TILESTATE::TTELEPORT;
				}
			}
			this->phase = INTROPHASE::INITBULLETHELL;
			break;
		case INTROPHASE::INITBULLETHELL:
			if ((*this->grid)[0][0].state == TILESTATE::TELEPORT && !this->teleported) {
				this->teleported = true;
			}
			else if (this->teleported)
			{
				indexX = (*this->grid).size() - 6;
				//	indexY = (*this->grid)[0].size() / 2;

				for (int i = 0; i < this->numSquareHorizontal; i++) {
					for (int j = 0; j < this->numSquareVertical; j++) {
						if ((i == indexX || i == indexX + 1) /*&& (j == indexY || j == indexY - 1)*/) {
							(*this->grid)[i][j].state = TILESTATE::BOSSTILE;
							this->tileIndex.push_back(Index(i, j));
						}
						else {
							(*this->grid)[i][j].state = TILESTATE::ACTIVE;
						}
					}
				}
				this->phase = INTROPHASE::BULLETHELL;
				this->teleported = false;
			}
			break;
		case INTROPHASE::BULLETHELL:
			// Update the counter
			this->counter += dt;
			// Make the boss attack
			this->pBrain->pushCommand(AICOMMANDS::BOSSATTACK01);
			// Create new wave if the time is right
			if (this->counter >= 0.2f) {
				// Create a new wave
				if (this->waveIterations == 10) {
					this->createNewWave();
					this->waveIterations = 0;
				}
				// Update the teleportation waves
				for (int i = 0; i < this->waves.size(); i++) {
					for (int j = 0; j < (*this->grid)[i].size(); j++) {
						(*this->grid)[this->waves[i].currentIndexX][j].state = TILESTATE::ACTIVE;
					}
					this->waves[i].currentIndexX--;
					if (this->waves[i].currentIndexX > 3) {
						for (int j = 0; j < (*this->grid)[i].size(); j++) {
							(*this->grid)[this->waves[i].currentIndexX][j].state = this->waves[i].pattern[j];
						}
					}
					else {
						this->waves.erase(this->waves.begin() + i);
						i--;
					}
				}
				// Reset the counter
				this->counter = 0.0f;
				this->waveIterations++;
			}
			// Check if the player managed to reach the boss tiles
			if (this->pGPS->GETplayerSteppedOnBossTile()) {
				for (int i = 0; i < this->numSquareHorizontal; i++) {
					for (int j = 0; j < this->numSquareVertical; j++) {
						(*this->grid)[i][j].state = TILESTATE::ACTIVE;
					}
				}
				this->phase = INTROPHASE::DAMAGEPHASE;
				this->pHead->turnOffInvulnerability();
				this->pGPS->SETplayerSteppedOnBossTile(false);
				this->counter = 0.0f;
			}
			break;
		case INTROPHASE::DAMAGEPHASE:
			//Update counter and make the boss invulnerable if the time is right.
			//Then start the battle loop from phase FIRST again.
			
			/*
			this->counter += dt;
			
			if (this->counter >= 4.0f) {
				this->phase = INTROPHASE::FIRST;
				this->pHead->turnOnInvulnerability();
				this->counter = 0.0f;
			}
			*/
			break;
		default:
			break;
		}
	}
}