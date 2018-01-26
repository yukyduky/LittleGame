#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <d3d11.h>
#include "D3D.h"
#include "Component.h"
#include <DirectXCollision.h>

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                     |
  |         PHYSICS COMPONENT           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/


class PhysicsComponent : public Component
{
private:
	DirectX::BoundingSphere selfBoundingSphere;
	const size_t ID;

	int collisionID;
	GameObject* tempCollidableHolder;
	DirectX::XMFLOAT3 pushVector;
	/// Might need to mess with XMVector and storing and shit, so that I can normalize
	float stepper = 0.1;

	int createCollisionID(GameObject* collidable1, GameObject* collidable2);

	void collisionPlayerPlayer(GameObject* collidable1, GameObject* collidable2);
	void collisionPlayerEnemy(GameObject* collidable1, GameObject* collidable2);
	void collisionPlayerDoodad(GameObject* collidable1, GameObject* collidable2);
	void collisionPlayerIndestruct(GameObject* collidable1, GameObject* collidable2);
	void collisionPlayerProjectile(GameObject* collidable1, GameObject* collidable2);
	void collisionEnemyEnemy(GameObject* collidable1, GameObject* collidable2);
	void collisionEnemyDoodad(GameObject* collidable1, GameObject* collidable2);
	void collisionEnemyIndestruct(GameObject* collidable1, GameObject* collidable2);
	void collisionEnemyProjectile(GameObject* collidable1, GameObject* collidable2);
	void collisionDoodadDoodad(GameObject* collidable1, GameObject* collidable2);
	void collisionDoodadIndestruct(GameObject* collidable1, GameObject* collidable2);
	void collisionDoodadProjectile(GameObject* collidable1, GameObject* collidable2);
	void collisionIndestructIndestruct(GameObject* collidable1, GameObject* collidable2);
	void collisionIndestrucProjectile(GameObject* collidable1, GameObject* collidable2);
	void collisionProjectileProjectile(GameObject* collidable1, GameObject* collidable2);

public:
	PhysicsComponent(GameObject& obj);
	PhysicsComponent(DirectX::XMFLOAT3 boundingSphereCenter, float radius, GameObject& obj);
	~PhysicsComponent();

	DirectX::BoundingSphere getBoundingSphere();
	bool checkCollision(DirectX::BoundingSphere boundingSphere_in);
	bool checkCollision(DirectX::BoundingBox boundingBox_in);

	void updateBoundingArea(DirectX::XMFLOAT3 centerPos);
	void updateBoundingArea(float radius);
	void updateBoundingArea(DirectX::XMFLOAT3 centerPos, float radius);

	void executeCollision(GameObject* collidable1, GameObject* collidable2);

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
};
//______________________________________________//
//                                              //
//           END OF PHYSICS COMPONENT           //
//______________________________________________//
//////////////////////////////////////////////////

#endif
