#pragma once
#ifndef GRAPHICSCOMPONENT_H_
#define GRAPHICSCOMPONENT_H_

#include "Component.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include <Windows.h>
#include "D3D.h"

class GraphicsComponent : Component
{
private:
	size_t ID;
	
public:
	const size_t getID();
	virtual void recieve(GameObject& obj, Message msg) = 0;
};

#endif
