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

	this->parentPointer = nullptr;
}

QuadTree::QuadTree(
	int level_in,
	float widthLength_in, float heightLength_in,
	float x_bottomLeftCorner, float y_bottomLeftCorner,
	QuadTree* parentPointer_in)
{
	this->level = level_in;
	this->midpointX = (x_bottomLeftCorner + (widthLength_in * 0.5));
	this->midpointY = (y_bottomLeftCorner + (heightLength_in * 0.5));

	this->nodeBounds.widthLength = widthLength_in;
	this->nodeBounds.heightLength = heightLength_in;
	this->nodeBounds.x = x_bottomLeftCorner;
	this->nodeBounds.y = y_bottomLeftCorner;

	this->nodes[BOTTOM_LEFT] = nullptr;
	this->nodes[BOTTOM_RIGHT] = nullptr;
	this->nodes[TOP_LEFT] = nullptr;
	this->nodes[TOP_RIGHT] = nullptr;

	this->parentPointer = parentPointer_in;
}

QuadTree::~QuadTree() {

}

//--------------------------------------------------------//
//  HELP-FUNCTIONS FOR THE 'initializeQuadTree' FUNCTION //
//------------------------------------------------------//
void QuadTree::split() {
	float tempWidth = (this->nodeBounds.widthLength * 0.5);
	float tempHeight = (this->nodeBounds.heightLength * 0.5);

	// Storing these so we don't have to 'get' them over and over
	float tempX = this->nodeBounds.x;
	float tempY = this->nodeBounds.y;

	this->nodes[BOTTOM_LEFT] = new QuadTree(
		(this->level + 1), tempWidth, tempHeight, tempX, tempY, this
	);
	this->nodes[BOTTOM_RIGHT] = new QuadTree(
		(this->level + 1), tempWidth, tempHeight, (tempX + tempWidth), tempY, this
	);
	this->nodes[TOP_LEFT] = new QuadTree(
		(this->level + 1), tempWidth, tempHeight, tempX, (tempY + tempHeight), this
	);
	this->nodes[TOP_RIGHT] = new QuadTree(
		(this->level + 1), tempWidth, tempHeight, (tempX + tempWidth), (tempY + tempHeight), this
	);
}

void QuadTree::splitRecursively(QuadTree* currentQuad) {
	for (int i = 0; i < 4; i++) {
		currentQuad->nodes[i]->split();

		if (currentQuad->nodes[i]->level < LAYERS_MAX) {
			this->splitRecursively(currentQuad->nodes[i]);
		}
	}
}
//-----------------------------------------------------//

void QuadTree::initializeQuadTree() {
	if (LAYERS_MAX > 0) {
		this->splitRecursively(this);
	}
}

void QuadTree::insertStaticObject(GameObject* staticObject) {
	int tempIndex;

	// Check if Quad Tree has additional Quad Tree nodes.
	// (Arbitrary node # from 0 and 3)
	if (this->nodes[0] != nullptr) {
		tempIndex = this->GETindex(staticObject);

		if (tempIndex == BOTTOM_LEFT)
			this->nodes[BOTTOM_LEFT]->insertStaticObject(staticObject);

		else if (tempIndex == BOTTOM_RIGHT)
			this->nodes[BOTTOM_RIGHT]->insertStaticObject(staticObject);

		else if (tempIndex == TOP_LEFT)
			this->nodes[TOP_LEFT]->insertStaticObject(staticObject);

		else if (tempIndex == TOP_RIGHT)
			this->nodes[TOP_RIGHT]->insertStaticObject(staticObject);

		// Object did not fully fit anywhere; pushing into parent QuadTree
		else if (tempIndex == -1)
			this->staticObjectsList.push_back(staticObject);
	}
	// nodes[0] = nullptr which means we've reached the end/bottom of our Quad Tree
	else {
		this->staticObjectsList.push_back(staticObject);
	}
}

void QuadTree::removeStaticObject(GameObject* staticObject) {
	QuadTree* tempQuadTreePointer = this;
	int tempIndex = this->GETindex(staticObject);

	// If there are nodes further down, then we...
	// Check if tempIndex = -1 (-1 = current QuadTree is holding the object)...
	// If both TRUE, search one level further down for the object.
	while (tempIndex != -1) {
		// Take one step further down into the QuadTree
		tempQuadTreePointer = this->nodes[tempIndex];
		// Find new index in the next layer, if another layer exists
		// ('0' here represents an arbitrary number from 0 to 3)
		if (tempQuadTreePointer->nodes[0] != nullptr)
			tempIndex = this->GETindex(staticObject);
	}

	tempQuadTreePointer->staticObjectsList.remove(staticObject);
}

int QuadTree::GETindex(GameObject* object) {
	// NOTE:	'tempIndex = -1' means that the object is within multiple quads simultaneously.
	//			The above case results in the parent quad holding the object.
	int tempIndex = -1;
	bool bottomHalf, topHalf;

	// BOTTOM HALF
	// TRUE if object is FULLY under parent-quad's 'midpointY'
	bottomHalf = ((object->GETPosition().y + object->GETphysicsComponent()->GETBoundingSphere().Radius) < this->midpointY);

	// TOP HALF
	// TRUE if object is FULLY above parent-quad's 'midpointY'
	topHalf = ((object->GETPosition().y + object->GETphysicsComponent()->GETBoundingSphere().Radius) > this->midpointY);

	// LEFT HALF
	// TRUE if object is FULLY ...
	if ((object->GETPosition().x + object->GETphysicsComponent()->GETBoundingSphere().Radius) < this->midpointX) {
		if (bottomHalf)
			tempIndex = BOTTOM_LEFT;
		else if (topHalf)
			tempIndex = TOP_LEFT;
	}
	// RIGHT HALF
	// TRUE if object is FULLY ...
	else if ((object->GETPosition().x + object->GETphysicsComponent()->GETBoundingSphere().Radius) > this->midpointX) {
		if (bottomHalf)
			tempIndex = BOTTOM_RIGHT;
		else if (topHalf)
			tempIndex = TOP_RIGHT;
	}

	return tempIndex;
}

void QuadTree::cleanup() {
	// Loops through one node at a time, looping through those nodes' 4 nodes, one at a time... etc.
	for (int i = 0; i < 4; i++) {
		if (this->nodes[i] != nullptr) {
			this->nodes[i]->cleanup();
		}
		// Delete each node as long as it's not the 'master Quad Tree' node, in which case we are done.
		if (this->level != 0) {
			delete this;
		}
	}
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

//void QuadTree::insertDynamicObject(GameObject* dynamicObject) {
//	int tempIndex;
//
//	// Check if Quad Tree has additional Quad Tree nodes.
//	// (Arbitrary node # from 0 and 3)
//	if (this->nodes[0] != nullptr) {
//		tempIndex = this->GETindex(dynamicObject);
//
//		if (tempIndex == BOTTOM_LEFT)
//			this->nodes[BOTTOM_LEFT]->insertStaticObject(dynamicObject);
//
//		else if (tempIndex == BOTTOM_RIGHT)
//			this->nodes[BOTTOM_RIGHT]->insertStaticObject(dynamicObject);
//
//		else if (tempIndex == TOP_LEFT)
//			this->nodes[TOP_LEFT]->insertStaticObject(dynamicObject);
//
//		else if (tempIndex == TOP_RIGHT)
//			this->nodes[TOP_RIGHT]->insertStaticObject(dynamicObject);
//
//		// Object did not fully fit anywhere; pushing into parent QuadTree
//		else if (tempIndex == -1)
//			this->dynamicObjectsList.push_back(dynamicObject);
//	}
//	// nodes[0] = nullptr which means we've reached the end/bottom of our Quad Tree
//	else {
//		this->dynamicObjectsList.push_back(dynamicObject);
//	}
//}