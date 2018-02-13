#pragma once
#ifndef QUADTREE_HP
#define QUADTREE_HP

#include "GameObject.h"
#include <list>
#include <d3d11.h>

// Currently initializing entire QuadTree at the start; OBJECT_MAX is withheld
///#define OBJECTS_MAX 20
#define LAYERS_MAX 5

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

	float midpointX;
	float midpointY;

	int level;
	std::list<GameObject*> staticObjectsList;
	QuadTreeSquare nodeBounds;
	QuadTree* nodes[4];

public:
	QuadTree();
	QuadTree(int level_in, float widthLength_in, float heightLength_in, float x_bottomLeftCorner, float y_bottomLeftCorner);
	~QuadTree();

	void split(QuadTree* currentQuad);
	void splitRecursively(QuadTree* currentQuad);
	void initializeQuadTree(int level_in, float widthLength_in, float heightLength_in, float x_bottomLeftCorner, float y_bottomLeftCorner);

	void insertStaticObject(GameObject* staticObject);
	void removeStaticObject(GameObject* staticObject);

	std::list<GameObject*> retrieveStaticList(GameObject* collidingObject);
	bool checkDynamicObject(GameObject* dynamicObject, GameObject* comparedObject);

	int GETindex(GameObject* object);

	void cleanup();
	void deleteToEnd(QuadTree* quadTree);
};

#endif