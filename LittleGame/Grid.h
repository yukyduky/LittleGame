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

/* GRIDSLOTS & EDGEGRIDSLOTS
Gridslots can be asked if there are any neighbours around, and they check the surrounding GridSlots.
EdgeGridSlots, however, delegate the responsibility of that action to a nearby gridslot who won't try to
access indices out of bounds.

*/
class EnemyObject;
class ArrayList;
class AliveNode;

class GridSlot {
public:
	Index index;
	std::list<EnemyObject*> occupants;

	virtual std::vector<EnemyObject*> getNeighbours(GridSlot** *pTheGrid) {
		Index center = this->index;
		std::vector<EnemyObject*> neighbours;
		std::vector<GridSlot*> potentialNeighbours;

		// Gather all the surrounding gridslots that can house potential neighbours
		potentialNeighbours.push_back(pTheGrid[center.x][center.y]);	// Center
		potentialNeighbours.push_back(pTheGrid[center.x - 1][center.y]);	// West
		potentialNeighbours.push_back(pTheGrid[center.x + 1][center.y]);	// East
		potentialNeighbours.push_back(pTheGrid[center.x][center.y + 1]);	// North
		potentialNeighbours.push_back(pTheGrid[center.x][center.y - 1]);	// South
		potentialNeighbours.push_back(pTheGrid[center.x - 1][center.y - 1]);	// Southwest
		potentialNeighbours.push_back(pTheGrid[center.x + 1][center.y - 1]);	// SouthEast
		potentialNeighbours.push_back(pTheGrid[center.x - 1][center.y + 1]);	// NorthWest
		potentialNeighbours.push_back(pTheGrid[center.x + 1][center.y + 1]);	// NorthEast

		// Get all found occupants
		for (auto &currentGridSlot : potentialNeighbours) {
			if (currentGridSlot->occupants.size() > 0) {
				for (auto &currentOccupant : currentGridSlot->occupants) {
					neighbours.push_back(currentOccupant);
				}
			}
		}

		return neighbours;
	}
	virtual void cleanUp() {
		this->occupants.clear();
	};
};
class EdgeGridSlot : public GridSlot {
private:
	GridSlot* substitute = nullptr;
public:
	void assignSubstitute(GridSlot* substitute) {
		this->substitute = substitute;
	}
	std::vector<EnemyObject*> getNeighbours(GridSlot** *pTheGrid) {
		return this->substitute->getNeighbours(pTheGrid);
	}
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
	GridSlot** *theGrid = nullptr;
	std::list<GridSlot*> occupiedSlots;

	void initialize(ArrayList*& arraylist);
	void wipeGrid();

	void updateFromOccupant(AliveNode* aliveNode);
	void updateOccupants();
	Index getIndex(XMFLOAT2 position);

public:
	Grid(ArrayList*& arraylist);

	void update();

	void removeSwarmer(int index);
	void activateNext();
	void activateMe(size_t swarmerID);

	// Not used, but might come in handy for something else later
	std::list<EnemyObject*>* getOccupants(XMFLOAT2 position);	// Slower than the index version.
	std::list<EnemyObject*>* getOccupants(Index index);	// Faster than the position version.

	std::vector<EnemyObject*> getNeighbours(XMFLOAT2 position);
	XMFLOAT3 getPositionToSeek();

	bool inOrOut(XMFLOAT2 position);
	// Like inOrOut but with a bit of marginal, so you're definitely inside.
	bool Grid::inOrOutPLUS(XMFLOAT2 position);
	bool gridAlive();

	void cleanUp();
};

#endif
