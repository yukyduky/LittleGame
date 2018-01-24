#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <d3d11.h>
#include "D3D.h"
#include "Component.h"

class PhysicsComponent : public Component
{
private:
	DirectX::BoundingBox selfBoundingBox;

public:
	PhysicsComponent();
	~PhysicsComponent();

	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;

	DirectX::BoundingBox getBoundingBox();

	void update(); //start with boundingbox
};

#endif
