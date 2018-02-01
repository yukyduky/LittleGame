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

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
};
//______________________________________________//
//                                              //
//           END OF PHYSICS COMPONENT           //
//______________________________________________//
//////////////////////////////////////////////////

#endif
