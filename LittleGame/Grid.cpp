#include "Grid.h"
#include "EnemyManager.h"
#include "ActorObject.h"
#include "EnemyObject.h"
#include "GameObject.h"

Grid::Grid(ArrayList* arrayList_)
{
	this->initialize(arrayList_);
}

void Grid::initialize(ArrayList* arrayList_)
{
	this->arrayList = arrayList_;
	this->levelOfDetail = 10;
	this->width = ARENAWIDTH;
	this->height = ARENAHEIGHT;
	this->widthDivider = this->width / levelOfDetail;
	this->heightDivider = this->height / levelOfDetail;

	// Allocation of the grid
	this->theGrid = new GridSlot*[levelOfDetail];
	for (int i = 0; i < levelOfDetail; i++) {
		this->theGrid[i] = new GridSlot[levelOfDetail];
	}

	// Initialization of every GridSlot
	for (int x = 0; x < levelOfDetail; x++) {
		for (int y = 0; y < levelOfDetail; y++) {

			this->theGrid[x][y].index = Index{ x, y };
		}
	}
}


void Grid::wipeGrid()
{
	this->occupiedSlots.clear();
}

void Grid::updateFromOccupant(AliveNode* aliveNode)
{
	// Find out which index this swarmer occupies
	EnemyObject* swarmer = aliveNode->index->obj;
	XMFLOAT3 position = swarmer->GETPosition();

	if (this->inOrOut(XMFLOAT2(position.x, position.z))) {
		// Add that swarmer to that GridSlot's 'occupants' list.
		Index occupiedIndex = this->getIndex(XMFLOAT2(position.x, position.z));
		GridSlot* occupiedGridSlot = &this->theGrid[occupiedIndex.x][occupiedIndex.y];
		occupiedGridSlot->occupants.push_back(swarmer);

		// Add that gridslot to the 'occupiedSlots' so that it's faster to clear them
		this->occupiedSlots.push_back(occupiedGridSlot);
	}
}

void Grid::updateOccupants()
{
	AliveNode* stepper = this->arrayList->getFirst();

	if (stepper != nullptr) {
		while (stepper->forward != nullptr) {
			this->updateFromOccupant(stepper);

			/// Step forward
			stepper = stepper->forward;
		}
		/// Do the last
		this->updateFromOccupant(stepper);
	}

}

Index Grid::getIndex(XMFLOAT2 position)
{
	Index index;
	index.x = (int)(position.x / this->widthDivider);
	index.y = (int)(position.y / this->heightDivider);
	return index;
}

void Grid::update()
{
	this->wipeGrid();
	this->updateOccupants();
}


std::list<EnemyObject*>* Grid::getOccupants(XMFLOAT2 position)
{
	Index index = getIndex(position);
	return &this->theGrid[index.x][index.y].occupants;
}

std::list<EnemyObject*>* Grid::getOccupants(Index index)
{
	return &this->theGrid[index.x][index.y].occupants;
}

std::vector<EnemyObject*> Grid::getNeighbours(XMFLOAT2 position)
{
	Index center = this->getIndex(position);
	std::vector<EnemyObject*> neighbours;
	std::vector<GridSlot*> potentialNeighbours;



	

	// Gather all the gridslots that can house potential neighbours
	potentialNeighbours.push_back(&this->theGrid[center.x][center.y]);	// Center
	potentialNeighbours.push_back(&this->theGrid[center.x - 1][center.y]);	// West
	potentialNeighbours.push_back(&this->theGrid[center.x + 1][center.y]);	// East
	potentialNeighbours.push_back(&this->theGrid[center.x][center.y + 1]);	// North
	potentialNeighbours.push_back(&this->theGrid[center.x][center.y - 1]);	// South
	potentialNeighbours.push_back(&this->theGrid[center.x - 1][center.y - 1]);	// Southwest
	potentialNeighbours.push_back(&this->theGrid[center.x + 1][center.y - 1]);	// SouthEast
	potentialNeighbours.push_back(&this->theGrid[center.x - 1][center.y + 1]);	// NorthWest
	potentialNeighbours.push_back(&this->theGrid[center.x + 1][center.y + 1]);	// NorthEast
	
	// Get all found occupants
	for (auto &currentGridSlot : potentialNeighbours) {
		if (currentGridSlot->occupants.size > 0) {
			for (auto &currentOccupant : currentGridSlot->occupants) {
				neighbours.push_back(currentOccupant);
			}
		}
	}

	/// A problem here is that an occupant asking for neighbours will recieve a vector where itself is included.
	return neighbours;
}

bool Grid::inOrOut(XMFLOAT2 position)
{
	bool result = false;
	
	if (position.x > 0 && position.x < ARENAWIDTH) {
		if (position.y > 0 && position.y < ARENAHEIGHT) {
			result = true;
		}
	}

	return result;
}

void Grid::cleanUp()
{
	for (int x = 0; x < levelOfDetail; x++) {
		
		for (int y = 0; y < levelOfDetail;) {
			// Cleans up the internal data inside the GridSlot
			this->theGrid[x][y].cleanUp();
		}

		// Deletes the Y-array
		delete this->theGrid[x];
	}
	// Deletes the X-array
	delete this->theGrid;
}