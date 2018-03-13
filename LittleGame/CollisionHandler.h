#pragma once
#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#define DISTANCE_FACTOR 1.414213f

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
// 3	=	PLAYER				+			GENERATOR
// 4	=	PLAYER				+			INDESTRUCTIBLE
// 5	=	PLAYER				+			PROJECTILE
// 6	=	PLAYER				+			BOSS

// E   N   E   M   Y
// 7	=	ENEMY				+			ENEMY
// 8	=	ENEMY				+			GENERATOR
// 9	=	ENEMY				+			INDESCTRUCTIBLE
// 10	=	ENEMY				+			PROJECTILE
// 11	=	ENEMY				+			BOSS

// D   O   O   D   A   D
// 12	=	GENERATOR			+			GENERATOR
// 13	=	GENERATOR			+			INDESTRUCTIBLE
// 14	=	GENERATOR			+			PROJECTILE
// 15	=	GENERATOR			+			BOSS

// I  N  D  E  S  T  R  U  C  T  I  B  L  E
// 16	=	INDESTRUCTIBLE		+			INDESTRUCTIBLE
// 17	=	INDESTRUCTIBLE		+			PROJECTILE
// 18	=	INDESTRUCTIBLE		+			BOSS

// P   R   O   J   E   C   T   I   L   E
// 19	=	PROJECTILE			+			PROJECTILE
// 20	=	PROJECTILE			+			BOSS

// B   O   S   S
// 21	=	BOSS				+			BOSS
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
	float distance = 0.0f;
	float xDiff = 0.0f;
	float zDiff = 0.0f;
	float minDiff = 0.0f;

	float stepper = 2.0f;

	int collisionID = 0;

	void createCollisionID();
	void calculateDistance(DirectX::XMFLOAT3 collidable1, DirectX::XMFLOAT3 collidable2);
	/*void calculateDistance(float x1, float y1, float x2, float y2);*/

	void collisionPlayerPlayer();
	void collisionPlayerEnemy();
	void collisionPlayerGenerator();
	void collisionPlayerIndestruct();
	void collisionPlayerProjectile();
	void collisionPlayerBoss();
	void collisionEnemyEnemy();
	void collisionEnemyGenerator();
	void collisionEnemyIndestruct();
	void collisionEnemyProjectile();
	void collisionEnemyBoss();
	void collisionGeneratorGenerator();
	void collisionGeneratorIndestruct();
	void collisionGeneratorProjectile();
	void collisionGeneratorBoss();
	void collisionIndestructIndestruct();
	void collisionIndestrucProjectile();
	void collisionIndestrucBoss();
	void collisionProjectileProjectile();
	void collisionProjectileBoss();
	void collisionBossBoss();

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