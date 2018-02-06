#pragma once
#ifndef QUADTREE_HP
#define QUADTREE_HP

#include "GameObject.h"
#include <list>
#include <d3d11.h>

#define OBJECTS_MAX = 20
#define LAYERS_MAX = 5

struct QuadTreeSquare {
	float widthLength;
	float heightLength;
	float x;
	float y;

	QuadTreeSquare();
	QuadTreeSquare(float widthLength_in, float heightLength_in, float x_in, float y_in);
};

class QuadTree {
private:
	enum QUADTREEINDEX { BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT, SIZE };

	int level;
	std::list<GameObject*> staticObjectsList;
	std::list<GameObject*> dynamicObjectsList;
	QuadTreeSquare nodeBounds;
	QuadTree* nodes[4];
	QuadTree* parentPointer;

public:
	QuadTree();
	QuadTree(int level_in, float widthLength_in, float heightLength_in, float x_bottomLeftCorner, float y_bottomLeftCorner, QuadTree* parentPointer_in);
	~QuadTree();

	void split();
	void insertStaticObject(GameObject* staticObject);
	void insertDynamicObject(GameObject* dynamicObject);
	void removeStaticObject();
	void removeDynamicObject();

	int GETIndex();

	void cleanup();
};

#endif
