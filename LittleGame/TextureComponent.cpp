#include "TextureComponent.h"
#include "D3D.h"


TextureComponent::TextureComponent(size_t ID, ID3D11ShaderResourceView* gSRV) : ID(ID), gSRV(gSRV)
{
	this->vertices[0] = TextureVertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f);
	this->vertices[1] = TextureVertex(-0.5f, 0.5f, 0.0f, 0.0f, 1.0f);
	this->vertices[2] = TextureVertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
	this->vertices[3] = TextureVertex(0.5f, 0.5f, 0.0f, 1.0f, 1.0f);
}

ID3D11ShaderResourceView * TextureComponent::getSRV()
{
	return this->gSRV;
}
