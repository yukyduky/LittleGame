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
	this->levelOfDetail = 10;		// Also decides how easily swarmers group up
	this->width = ARENAWIDTH;
	this->height = ARENAHEIGHT;
	this->widthDivider = this->width / levelOfDetail;
	this->heightDivider = this->height / levelOfDetail;

	// Allocation of the grid
	this->theGrid = new GridSlot**[levelOfDetail];
	for (int i = 0; i < levelOfDetail; i++) {
		this->theGrid[i] = new GridSlot*[levelOfDetail];
	}

	// Initialization of every GridSlot
	for (int x = 0; x < levelOfDetail; x++) {
		for (int y = 0; y < levelOfDetail; y++) {
			/// Is it on the edge?
			// West edge
			if (x == 0) {
				this->theGrid[x][y] = new EdgeGridSlot();
			}
			// North edge
			else if (y == levelOfDetail-1) {
				this->theGrid[x][y] = new EdgeGridSlot();
			}
			// East edge
			else if (x == levelOfDetail-1) {
				this->theGrid[x][y] = new EdgeGridSlot();
			}
			// South edge
			else if (y == 0) {
				this->theGrid[x][y] = new EdgeGridSlot();
			}
			// If it's not on the edge, allocate a normal GridSlot
			else {
				this->theGrid[x][y] = new GridSlot();
			}
			
			this->theGrid[x][y]->index = Index{ x, y };
		}
	}

	/// Assign substitutes to all of the EdgeGridSlots
	// West
	for (int y = 0; y < levelOfDetail; y++) {
		EdgeGridSlot* trueForm = static_cast<EdgeGridSlot*>(this->theGrid[0][y]);
		trueForm->assignSubstitute(this->theGrid[1][y]);
	}
	// East
	for (int y = 0; y < levelOfDetail; y++) {
		EdgeGridSlot* trueForm = static_cast<EdgeGridSlot*>(this->theGrid[levelOfDetail - 1][y]);
		trueForm->assignSubstitute(this->theGrid[levelOfDetail - 2][y]);
	}
	// North
	for (int x = 0; x < levelOfDetail; x++) {
		EdgeGridSlot* trueForm = static_cast<EdgeGridSlot*>(this->theGrid[x][levelOfDetail - 1]);
		trueForm->assignSubstitute(this->theGrid[x][levelOfDetail - 2]);
	}
	// South
	for (int x = 0; x < levelOfDetail; x++) {
		EdgeGridSlot* trueForm = static_cast<EdgeGridSlot*>(this->theGrid[x][0]);
		trueForm->assignSubstitute(this->theGrid[x][1]);
	}

	// PURELY FOR TESTING, REMOVE IF YOU WISH
	for (int x = 0; x < levelOfDetail; x++) {
		for (int y = 0; y < levelOfDetail; y++) {
			this->theGrid[x][y]->getNeighbours(this->theGrid);
		}
	}
}


void Grid::wipeGrid()
{
	for (auto gridSlotWithOccupants : this->occupiedSlots) {
		gridSlotWithOccupants->occupants.clear();
	}
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
		GridSlot* occupiedGridSlot = this->theGrid[occupiedIndex.x][occupiedIndex.y];
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

void Grid::removeSwarmer(int index)
{
	this->arrayList->remove(index);
}

void Grid::activateNext()
{
	this->arrayList->activateNext();
}

void Grid::activateMe(size_t swarmerID)
{
	this->arrayList->activateMe(swarmerID);
}


std::list<EnemyObject*>* Grid::getOccupants(XMFLOAT2 position)
{
	Index index = getIndex(position);
	return &this->theGrid[index.x][index.y]->occupants;
}

std::list<EnemyObject*>* Grid::getOccupants(Index index)
{
	return &this->theGrid[index.x][index.y]->occupants;
}

std::vector<EnemyObject*> Grid::getNeighbours(XMFLOAT2 position)
{
	std::vector<EnemyObject*> neighbours;
	Index index = this->getIndex(position);

	// Only try to return neighbours if the position is inside the grid.
	if (this->inOrOut(position)) {
		neighbours = this->theGrid[index.x][index.y]->getNeighbours(this->theGrid);
	}

	return neighbours;
}

XMFLOAT3 Grid::getPositionToSeek()
{
	return this->arrayList->getAveragePosition();
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
bool Grid::inOrOutPLUS(XMFLOAT2 position) 
{
	bool result = false;
	int margin = LENGTHOFWALLS * ARENASQUARESIZE + 1;

	if ((position.x > margin) && (position.x < ARENAWIDTH - margin)) {
		if ((position.y > margin) && (position.y < ARENAHEIGHT - margin)) {
			result = true;
		}
	}

	return result;
}

void Grid::cleanUp()
{
	/// NOT UPDATED
	for (int x = 0; x < levelOfDetail; x++) {
		for (int y = 0; y < levelOfDetail; y++) {
			// Cleans up the internal data inside the GridSlot
			this->theGrid[x][y]->cleanUp();
			// Deletes the allocated GridSlot
			delete this->theGrid[x][y];
		}
		// Deletes the Y-array
		delete this->theGrid[x];
	}
	// Deletes the X-array
	delete this->theGrid;
}