#pragma once
#ifndef GRID_H
#define GRID_H

#include "SwarmerState.h"
#include "ActorObject.h"
#include "LevelManager.h"


class EnemyObject;

struct Index 
{
	int x = -1;
	int y = -1;
};
struct GridSlot
{
	Index index;
	std::list<EnemyObject*> occupants;
	
	void cleanUp() {
		this->occupants.clear();
	};
};

class Grid
{
private:
	int widthLength = -1;
	int heightLength = -1;
	GridSlot** theGrid;
	GridSlot* occupiedSlots;

	void wipeGrid();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1.
	*/
	void updateOccupants();
	Index convertPositionIntoIndex(XMFLOAT2 position);

public:
	Grid();
	void initialize();

	void update();

	

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Two alternatives, where position is the slowest one.
	*/
	std::list<EnemyObject*>* getOccupants(XMFLOAT2 position);
	std::list<EnemyObject*>* getOccupants(Index index);

	void cleanUp();

};

#endif
