#include "TextureComponent.h"
#include "Locator.h"
#include "GameObject.h"


TextureComponent::TextureComponent(size_t ID, ID3D11ShaderResourceView* gSRV) : ID(ID), gSRV(gSRV)
{
}

const size_t TextureComponent::getID()
{
	return -1;
}
void TextureComponent::receive(GameObject& obj, Message msg)
{

}

void TextureComponent::update()
{

}

void TextureComponent::cleanUp()
{
	// Maybe release this->gSRV here, maybe somewhere else
}

ID3D11ShaderResourceView * TextureComponent::getSRV()
{
	return this->gSRV;
}

XMMATRIX& TextureComponent::getWorld()
{
	return XMMATRIX();
}
