#include "QuadTree.h"
#include "PhysicsComponent.h"

QuadTreeSquare::QuadTreeSquare() {
	this->widthLength = 0;
	this->heightLength = 0;
	this->x = 0;
	this->y = 0;
}

QuadTreeSquare::QuadTreeSquare(float widthLength_in, float heightLength_in, float x_in, float y_in) {
	this->widthLength = widthLength_in;
	this->heightLength = heightLength_in;
	this->x = x_in;
	this->y = y_in;
}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                                     QUAD TREE           /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/
//_________________________________________//
//                                         //
//             END OF PRIVATE              //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PUBLIC            |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

QuadTree::QuadTree() {
	this->level = 0;
	this->midpointX = 0;
	this->midpointY = 0;

	this->nodes[BOTTOM_LEFT] = nullptr;
	this->nodes[BOTTOM_RIGHT] = nullptr;
	this->nodes[TOP_LEFT] = nullptr;
	this->nodes[TOP_RIGHT] = nullptr;
}

QuadTree::QuadTree(
	int level_in,
	float widthLength_in, float heightLength_in,
	float x_bottomLeftCorner, float y_bottomLeftCorner)
{
	this->level = level_in;

	this->nodeBounds.widthLength = widthLength_in;
	this->nodeBounds.heightLength = heightLength_in;
	this->nodeBounds.x = x_bottomLeftCorner;
	this->nodeBounds.y = y_bottomLeftCorner;

	this->midpointX = (x_bottomLeftCorner + (widthLength_in * 0.5));
	this->midpointY = (y_bottomLeftCorner + (heightLength_in * 0.5));

	this->nodes[BOTTOM_LEFT] = nullptr;
	this->nodes[BOTTOM_RIGHT] = nullptr;
	this->nodes[TOP_LEFT] = nullptr;
	this->nodes[TOP_RIGHT] = nullptr;
}

QuadTree::~QuadTree() {

}

//--------------------------------------------------------//
//  HELP-FUNCTIONS FOR THE 'initializeQuadTree' FUNCTION //
//------------------------------------------------------//
void QuadTree::split(QuadTree* currentQuad) {
	float width = (currentQuad->nodeBounds.widthLength * 0.5);
	float height = (currentQuad->nodeBounds.heightLength * 0.5);

	// Storing these so we don't have to 'get' them over and over
	float storedX = currentQuad->nodeBounds.x;
	float storedY = currentQuad->nodeBounds.y;

	currentQuad->nodes[BOTTOM_LEFT] = new QuadTree(
		(currentQuad->level + 1), width, height, storedX, storedY
	);
	currentQuad->nodes[BOTTOM_RIGHT] = new QuadTree(
		(currentQuad->level + 1), width, height, (storedX + width), storedY
	);
	currentQuad->nodes[TOP_LEFT] = new QuadTree(
		(currentQuad->level + 1), width, height, storedX, (storedY + height)
	);
	currentQuad->nodes[TOP_RIGHT] = new QuadTree(
		(currentQuad->level + 1), width, height, (storedX + width), (storedY + height)
	);
}

void QuadTree::splitRecursively(QuadTree* currentQuad) {
	currentQuad->split(currentQuad);

	// '0' represents an arbitrary number from 0 to 3
	if (currentQuad->nodes[0]->level < LAYERS_MAX) {
		for (int i = 0; i < 4; i++) {
			currentQuad->splitRecursively(currentQuad->nodes[i]);
		}
	}
}
//-----------------------------------------------------//

void QuadTree::initializeQuadTree(
	int level_in,
	float widthLength_in, float heightLength_in,
	float x_bottomLeftCorner, float y_bottomLeftCorner) {

	this->level = level_in;

	this->nodeBounds.widthLength = widthLength_in;
	this->nodeBounds.heightLength = heightLength_in;
	this->nodeBounds.x = x_bottomLeftCorner;
	this->nodeBounds.y = y_bottomLeftCorner;

	this->midpointX = (x_bottomLeftCorner + (widthLength_in * 0.5));
	this->midpointY = (y_bottomLeftCorner + (heightLength_in * 0.5));

	if (LAYERS_MAX > 0) {
		this->splitRecursively(this);
	}
}

void QuadTree::insertStaticObject(GameObject* staticObject) {
	QuadTree* quadTreePointer = this;
	int index;

	// Check if Quad Tree has additional Quad Tree nodes.
	// (Arbitrary node # from 0 and 3)
	if (quadTreePointer->nodes[0] != nullptr) {
		index = quadTreePointer->GETindex(staticObject);

		while (index != -1) {
			quadTreePointer = quadTreePointer->nodes[index];
			index = quadTreePointer->GETindex(staticObject);
		}

		quadTreePointer->staticObjectsList.push_back(staticObject);
	}
	// First QuadTree did not have any additional nodes, so it gets the object
	else {
		quadTreePointer->staticObjectsList.push_back(staticObject);
	}
}

void QuadTree::removeStaticObject(GameObject* staticObject) {
	QuadTree* quadTreePointer = this;
	int index = this->GETindex(staticObject);

	// index != -1 means that we need to traverse deeper into the QuadTree
	while (index != -1) {
		// Take one step further down into the QuadTree
		quadTreePointer = quadTreePointer->nodes[index];
		index = quadTreePointer->GETindex(staticObject);
	}

	quadTreePointer->staticObjectsList.remove(staticObject);
}

std::list<GameObject*> QuadTree::retrieveStaticList(GameObject* collidingObject) {
	QuadTree* quadTreePointer = this;
	std::list<GameObject*> staticObjectList;
	int indexHolder = this->GETindex(collidingObject);

	while (indexHolder != -1) {
		// We grab all objects in the parent QuadTree, then continue traversing
		staticObjectList.insert(
			staticObjectList.end(),
			quadTreePointer->staticObjectsList.begin(),
			quadTreePointer->staticObjectsList.end()
		);

		quadTreePointer = quadTreePointer->nodes[indexHolder];
		indexHolder = quadTreePointer->GETindex(collidingObject);
	}
	// This catches the last list, which we wouldn't get otherwise
	staticObjectList.insert(
		staticObjectList.end(),
		quadTreePointer->staticObjectsList.begin(),
		quadTreePointer->staticObjectsList.end()
	);

	return staticObjectList;
}

bool QuadTree::checkDynamicObject(GameObject* dynamicObject, GameObject* comparedObject) {
	QuadTree* quadTreePointer = this;
	bool returnValue = false;
	int indexDynamic = quadTreePointer->GETindex(dynamicObject);
	int indexCompared = quadTreePointer->GETindex(comparedObject);

	while (indexDynamic == indexCompared) {
		quadTreePointer = quadTreePointer->nodes[indexDynamic];

		int indexDynamic = quadTreePointer->GETindex(dynamicObject);
		int indexCompared = quadTreePointer->GETindex(comparedObject);

		if (indexDynamic == -1) {
			returnValue = true;
			break;
		}
	}

	return returnValue;
}

int QuadTree::GETindex(GameObject* object) {
	// NOTE:	'index = -1' means that the object is within multiple quads simultaneously.
	//			The above case results in the parent quad holding the object.
	int index = -1;
	bool bottomHalf, topHalf;

	// If 'this' QuadTree doesn't have nodes, return -1
	if (this != nullptr && this->nodes[0] != nullptr) {
		// BOTTOM HALF
		// TRUE if object is FULLY under parent-quad's 'midpointY'
		bottomHalf = ((object->GETPosition().z + object->GETphysicsComponent()->GETBoundingSphere().Radius) < this->midpointY);

		// TOP HALF
		// TRUE if object is FULLY above parent-quad's 'midpointY'
		topHalf = ((object->GETPosition().z - object->GETphysicsComponent()->GETBoundingSphere().Radius) > this->midpointY);

		// LEFT HALF
		// TRUE if object is FULLY ...
		if ((object->GETPosition().x + object->GETphysicsComponent()->GETBoundingSphere().Radius) < this->midpointX) {
			if (bottomHalf)
				index = BOTTOM_LEFT;
			else if (topHalf)
				index = TOP_LEFT;
		}
		// RIGHT HALF
		// TRUE if object is FULLY ...
		else if ((object->GETPosition().x - object->GETphysicsComponent()->GETBoundingSphere().Radius) > this->midpointX) {
			if (bottomHalf)
				index = BOTTOM_RIGHT;
			else if (topHalf)
				index = TOP_RIGHT;
		}
	}

	return index;
}

void QuadTree::cleanup() {
	// Loops through one node at a time, looping through those nodes' 4 nodes, one at a time... etc.
	if (LAYERS_MAX > 0) {
		for (int i = 0; i < 4; i++) {
			this->deleteToEnd(this->nodes[i]);
		}
	}
}

void QuadTree::deleteToEnd(QuadTree* currentQuad) {
	if (currentQuad->nodes[0] != nullptr) {
		for (int i = 0; i < 4; i++) {
			currentQuad->deleteToEnd(currentQuad->nodes[i]);
		}
	}

	delete currentQuad;
}

//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                                      QUAD TREE          \
////////////////////////////////////////////////////////////
