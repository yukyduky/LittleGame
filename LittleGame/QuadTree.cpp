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
	this->nodeBounds.widthLength = widthLength_in;
	this->nodeBounds.heightLength = heightLength_in;
	this->nodeBounds.x = x_bottomLeftCorner;
	this->nodeBounds.y = y_bottomLeftCorner;
	this->parentPointer = parentPointer_in;
}

QuadTree::~QuadTree() {

}

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

void QuadTree::cleanup() {
	for (int i = 0; i < 4; i++) {
		if (this->)
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