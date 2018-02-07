#include "QuadTree.h"

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

int QuadTree::GETindex(GameObject* object) {
	int tempIndex = -1;
	bool bottomHalf, topHalf, leftHalf, rightHalf;

	// BOTTOM HALF
	bottomHalf = (object->getPosition().y + object->get)

	// TOP HALF


	// LEFT HALF


	// RIGHT HALF

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