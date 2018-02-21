#pragma once
#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#define DISTANCE_FACTOR 1.4142135623730950488016887242097

#include <d3d11.h>
#include "D3D.h"
#include "Component.h"
#include <DirectXCollision.h>
#include "GameObject.h"
#include <SimpleMath.h>
#include <DirectXMath.h>

using namespace SimpleMath;

// COLLIDABLE ID-LIST:
/*
// P   L   A   Y   E   R
// 1	=	PLAYER				+			PLAYER
// 2	=	PLAYER				+			ENEMY
// 3	=	PLAYER				+			DOODAD
// 4	=	PLAYER				+			INDESTRUCTIBLE
// 5	=	PLAYER				+			PROJECTILE

// E   N   E   M   Y
// 6	=	ENEMY				+			ENEMY
// 7	=	ENEMY				+			DOODAD
// 8	=	ENEMY				+			INDESCTRUCTIBLE
// 9	=	ENEMY				+			PROJECTILE

// D   O   O   D   A   D
// 10	=	DOODAD				+			DOODAD
// 11	=	DOODAD				+			INDESTRUCTIBLE
// 12	=	DOODAD				+			PROJECTILE

// I  N  D  E  S  T  R  U  C  T  I  B  L  E
// 13	=	INDESTRUCTIBLE		+			INDESTRUCTIBLE
// 14	=	INDESTRUCTIBLE		+			PROJECTILE

// P   R   O   J   E   C   T   I   L   E
// 15	=	PROJECTILE			+			PROJECTILE
*/

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                     |
  |         COLLISION HANDLER           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

class CollisionHandler {
private:
	GameObject* collidable1 = nullptr;
	GameObject* collidable2 = nullptr;
	DirectX::BoundingSphere* boundingArea1 = nullptr;
	DirectX::BoundingSphere* boundingArea2 = nullptr;

	// Needed for swapping places of collidable1 with collidable2
	GameObject* tempCollidableHolder = nullptr;

	DirectX::XMFLOAT3 centerToCenterVector;
	DirectX::XMFLOAT3 resultVector;
	DirectX::XMFLOAT3 resultVector1;
	float radiusDistanceVector = 0.0f;
	float divisionFactor = 0.0f;

	// calculateDistance variables
	double distance = 0;
	double xDiff = 0;
	double zDiff = 0;
	double minDiff = 0;

	float stepper = 2.0;

	int collisionID = 0;

	void createCollisionID();
	void calculateDistance(DirectX::XMFLOAT3 collidable1, DirectX::XMFLOAT3 collidable2);
	/*void calculateDistance(float x1, float y1, float x2, float y2);*/

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