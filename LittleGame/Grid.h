#pragma once
#ifndef GRID_H
#define GRID_H


#include "ActorObject.h"
#include "LevelManager.h"
#include "FloorFallPatterns.h"	 // For struct 'Index'

/* GRID
This class is used by swarmers when they want to see if there are any nearby swarmers(neighbours).
They accomplish this by giving the grid their position and recieving any swarmers occupying the same or surrounding
index slots.

The grid updates by clearing all previously occupied slots and afterwards goes through the arrayList of active swarmers,
checking their positions and alerting different gridslots that they are being occupied and by whom.
*/

class EnemyObject;
class ArrayList;
class AliveNode;

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
	int levelOfDetail = -1;
	int width = -1;
	int height = -1;
	float widthDivider = -1;
	float heightDivider = -1;
	
	ArrayList* arrayList = nullptr;
	GridSlot** theGrid = nullptr;
	std::list<GridSlot*> occupiedSlots;

	void initialize(ArrayList* arraylist);
	void wipeGrid();

	void updateFromOccupant(AliveNode* aliveNode);
	void updateOccupants();
	Index getIndex(XMFLOAT2 position);

public:
	Grid(ArrayList* arraylist);
	

	void update();


	std::list<EnemyObject*>* getOccupants(XMFLOAT2 position);	// Slower than the index version.
	std::list<EnemyObject*>* getOccupants(Index index);	// Faster than the position version.
	std::vector<EnemyObject*> getNeighbours(XMFLOAT2 position);
	bool inOrOut(XMFLOAT2 position);

	void cleanUp();

};

#endif
