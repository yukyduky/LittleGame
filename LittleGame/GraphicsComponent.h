#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"

struct PrimitiveVertex
{
	float x, y, z;
	float r, g, b;
};

struct TextureVertex
{
	float x, y, z;
	float tx, ty;

	TextureVertex(float x, float y, float z, float tx, float ty) : x(x), y(y), z(z), tx(tx), ty(ty) {}
	TextureVertex() {}
};

class GraphicsComponent : public Component
{
public:
	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;
};

#endif // !GRAPHICSCOMPONENT_H
