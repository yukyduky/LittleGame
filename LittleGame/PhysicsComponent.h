#pragma once
#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <d3d11.h>
#include "D3D.h"

class PhysicsComponent
{
private:
	DirectX::BoundingBox selfBoundingBox;

public:
	PhysicsComponent();
	~PhysicsComponent();

	DirectX::BoundingBox getBoundingBox();
};

#endif
