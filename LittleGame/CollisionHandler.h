#pragma once
#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#define DISTANCE_FACTOR 1.4142135623730950488016887242097

#include <d3d11.h>
#include "D3D.h"
#include "Component.h"
#include <DirectXCollision.h>
#include "GameObject.h"

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                     |
  |         COLLISION HANDLER           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

class CollisionHandler {
private:
	GameObject* collidable1;
	GameObject* collidable2;
	DirectX::BoundingSphere* boundingArea1;
	DirectX::BoundingSphere* boundingArea2;

	// Needed for swapping places of collidable1 with collidable2
	GameObject* tempCollidableHolder;

	DirectX::XMFLOAT3 centerToCenterVector;
	DirectX::XMFLOAT3 resultVector;
	float radiusDistanceVector;
	float divisionFactor;

	// calculateDistance variables
	double distance;
	double xDiff;
	double yDiff;
	double minDiff;

	float stepper = 2.0;

	int collisionID;

	int createCollisionID();
	void calculateDistance(float x1, float y1, float x2, float y2);

	void collisionPlayerPlayer();
	void collisionPlayerEnemy();
	void collisionPlayerDoodad();
	void collisionPlayerIndestruct();
	void collisionPlayerProjectile();
	void collisionEnemyEnemy();
	void collisionEnemyDoodad();
	void collisionEnemyIndestruct();
	void collisionEnemyProjectile();
	void collisionDoodadDoodad();
	void collisionDoodadIndestruct();
	void collisionDoodadProjectile();
	void collisionIndestructIndestruct();
	void collisionIndestrucProjectile();
	void collisionProjectileProjectile();

public:
	CollisionHandler();
	~CollisionHandler();

	void executeCollision(
		GameObject* collidable1,
		GameObject* collidable2,
		DirectX::BoundingSphere* boundingArea1,
		DirectX::BoundingSphere* boundingArea2);
};

#endif