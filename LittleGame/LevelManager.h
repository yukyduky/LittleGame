#pragma once
#ifndef LEVELMANAGER_H_
#define LEVELMANAGER_H_

#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"

using namespace DirectX::SimpleMath;

class LevelManager
{
private:
	int arenaWidth;
	int arenaDepth;
	int squareSize;
	int wallHeight;
	

	void createFloor(std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics);
	void createNeonFloorGrid(std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics);
	void createARectLine(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics);
	void createLevelWalls(std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics, std::vector<PhysicsComponent*>& physics);
	void createAWall(XMFLOAT3 pos, XMFLOAT3 scale, XMMATRIX worldM, XMFLOAT4 color, std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics, std::vector<PhysicsComponent*>& physics);



	//void randomize();

public:
	void initArena(int width, int depth, std::array<int*, 0>& grid, std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics, std::vector<PhysicsComponent*>& physics);


};



#endif