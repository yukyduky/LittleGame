#pragma once
#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include "GraphicsComponent.h"
#include <array>

struct ID3D11ShaderResourceView;


class TextureComponent : public GraphicsComponent
{
protected:
	const size_t ID;
	ID3D11ShaderResourceView* gSRV;
public:
	TextureComponent(size_t ID, ID3D11ShaderResourceView* gSRV);

	virtual const size_t getID();
	virtual void receive(GameObject& obj, Message msg);
	virtual void cleanUp();

	ID3D11ShaderResourceView* getSRV();
	virtual XMMATRIX& getWorld();
};

#endif // !TEXTURECOMPONENT_H
