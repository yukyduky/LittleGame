#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"

namespace OBJECTTYPE {
	enum TYPE { BLOCK, SIZE };
}

struct PrimitiveColor
{
	float r, g, b, a;

	PrimitiveColor(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a){}
	PrimitiveColor(){}
};

struct PrimitiveVertex
{
	float x, y, z;
	
	PrimitiveVertex(float x, float y, float z)
		: x(x), y(y), z(z){}
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
