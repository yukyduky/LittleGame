#pragma once
#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

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
	DirectX::XMFLOAT3 centerDistanceVector;
	DirectX::XMFLOAT3 radiusDistanceVector;
	DirectX::XMFLOAT3 resultVector;
	float stepper = 0.01;

	int collisionID;

	int createCollisionID();

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