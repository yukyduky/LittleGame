#include "TextureComponent.h"
#include "Locator.h"


TextureComponent::TextureComponent(size_t ID, ID3D11ShaderResourceView* gSRV) : ID(ID), gSRV(gSRV)
{
}

ID3D11ShaderResourceView * TextureComponent::getSRV()
{
	return this->gSRV;
}

XMMATRIX& TextureComponent::getWorld()
{
	return XMMATRIX();
}
