#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <d3d11.h>
#include "D3D.h"
#include "Component.h"
#include "QuadTree.h"
#include <DirectXCollision.h>

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                     |
  |         PHYSICS COMPONENT           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/


class PhysicsComponent : public Component
{
private:
	GameObject* pHead;
	DirectX::BoundingSphere selfBoundingSphere;
	//DirectX::BoundingBox selfBoundingBox;
	const size_t ID;

public:
	PhysicsComponent(GameObject& obj);
	PhysicsComponent(GameObject& obj, float boundingSphereRadius);
	virtual ~PhysicsComponent();

	bool checkCollision(DirectX::BoundingSphere boundingSphere_in);
	bool checkCollision(DirectX::BoundingBox boundingBox_in);

	void updateBoundingArea(DirectX::XMFLOAT3 centerPos);
	void updateBoundingArea(float radius);
	void updateBoundingArea(DirectX::XMFLOAT3 centerPos, float radius);

	GameObject*				GETpHead();
	DirectX::BoundingSphere	GETBoundingSphere();

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void update();
	virtual void cleanUp();
};
//______________________________________________//
//                                              //
//           END OF PHYSICS COMPONENT           //
//______________________________________________//
//////////////////////////////////////////////////

#endif
