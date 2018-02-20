#include "Grid.h"

Grid::Grid()
{

}

void Grid::wipeGrid()
{
	this->occupiedSlots.clear();
}

void Grid::updateOccupants()
{
	//for (each swarmer) {
	//	
	//	// Find out which index this swarmer occupies

	//	// Add that swarmer to that GridSlot's 'occupants' list.

	//	// If that index hasn't already been added, add it to the index list.
	//}
}

Index Grid::convertPositionIntoIndex(XMFLOAT2 position)
{
	return Index();
}

void Grid::initialize()
{
	int levelOfDetail = 10;
	int widthLength = ARENAWIDTH / levelOfDetail;
	int heightLength = ARENAHEIGHT / levelOfDetail;

	// Allocation of the grid
	this->theGrid = new GridSlot*[widthLength];
	for (int i = 0; i < heightLength; i++) {
		this->theGrid[i] = new GridSlot[heightLength];
	}

	// Initialization of every GridSlot
	for (int x = 0; x < widthLength; x++) {
		for (int y = 0; y < heightLength; y++) {

			this->theGrid[x][y].index = Index{ x, y };
		}
	}
}

void Grid::update()
{
	/*
	Each frame:
	- All data from the previous frame is wiped 
	- Each occupant is added to the grid again.

	Why not update their position? rather than wiping all and then adding again?
	- Each Gridslot has multiple occupants.
	- When updating, an occupant needs to both be able to find themselves(pro array) and the occupantArray itself
	needs to be able to expand flexibly(pro list), so whichever we choose it's bad.

	How is wiping better?
	- It is better, with the assumption that going through a list of all the occupants once per frame,
	is better than each occupant needing to find themselves each frame.

	Finishing thoughts:
	Occupants in a gridslot could be held there in arrays, but these would all need to be the size of 
	the maximum amount of occupants. Ultimately thinking about the problem is more useful than any one 
	chosen solution since the impact is minimal anyway.
	*/
	this->wipeGrid();
	this->updateOccupants();
}


std::list<EnemyObject*>* Grid::getOccupants(XMFLOAT2 position)
{
	Index index = convertPositionIntoIndex(position);
	return &this->theGrid[index.x][index.y].occupants;
}

std::list<EnemyObject*>* Grid::getOccupants(Index index)
{
	return &this->theGrid[index.x][index.y].occupants;
}

void Grid::cleanUp()
{
	for (int x = 0; x < widthLength; x++) {
		
		for (int y = 0; y < heightLength;) {
			// Cleans up the internal data inside the GridSlot
			this->theGrid[x][y].cleanUp();
		}

		// Deletes the Y-array
		delete this->theGrid[x];
	}
	// Deletes the X-array
	delete this->theGrid;
}