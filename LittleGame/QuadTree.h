//#pragma once
//#ifndef QUADTREE_HP
//#define QUADTREE_HP
//
//#include "GameObject.h"
//#include <list>
//#include <d3d11.h>
//
//#define OBJECTS_MAX = 20
//#define LAYERS_MAX = 5
//
//enum class QUADTREEINDEX { BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT };
//
//struct QuadTreeSquare {
//	int sideLength;
//	int x;
//	int y;
//	
//	QuadTreeSquare();
//	QuadTreeSquare(int sideLength_in, int x_in, int y_in);
//};
//
//class QuadTree {
//private:
//	int level;
//	std::list<GameObject*> staticObjectsList;
//	std::list<GameObject*> dynamicObjectsList;
//	QuadTreeSquare nodeBounds;
//	QuadTree* nodes[4];
//
//public:
//	QuadTree(int level_in, int nodeSideLength, int x_bottomLeftCorner, int y_bottomLeftCorner);
//	~QuadTree();
//
//	void split();
//	int getIndex();
//	void insertObject();
//	void removeObject();
//
//
//	void cleanup();
//};
//
//#endif
