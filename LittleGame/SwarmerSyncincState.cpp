#include "SwarmerSyncingState.h"

SwarmerSyncingState::SwarmerSyncingState(
	EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID
) : SwarmerState(pHead, pBrain, pGrid_, swarmerID)
{
	int asdf = 3;
}

void SwarmerSyncingState::executeBehavior()
{
	/*
	CURRENTLY DOES NOT TAKE PULSATING IN ACCOUNT

	updateNeighbours();

	vector = separation();
	vector = alignment();
	vector = cohesion();

	vector.normalize(); <- as XMVECTOR

	vector.birdify(rand)
	
	this->pBrain->pushCommand(COMMMAND::MOVE)	// Wavey vector already set.
	*/
}