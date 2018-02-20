#include "MenuObject.h"
#include "Component.h"

MenuObject::MenuObject(ID2D1HwndRenderTarget* RT) : ID(0), pRT(RT)
{
	//Default background
	D2D1_SIZE_F rtSize = pRT->GetSize();
	rectangle = D2D1::RectF(
		rtSize.width / 2 - this->menuSize.x,
		rtSize.height / 2 - this->menuSize.y,
		rtSize.width / 2 + this->menuSize.x,
		rtSize.height / 2 + this->menuSize.y
	);

	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkCyan), &this->pColorBrush);
}

MenuObject::MenuObject(ID2D1HwndRenderTarget* RT ,size_t ID, XMFLOAT4 pos, D2D1::ColorF color) : ID(ID), pRT(RT)
{
	D2D1_SIZE_F rtSize = pRT->GetSize();
	this->rectangle = D2D1::RectF(
		rtSize.width / 2 - this->menuSize.x +	pos.x,
		rtSize.height / 2 - this->menuSize.y +	pos.y,
		rtSize.width / 2 - this->menuSize.x +	pos.z,
		rtSize.height / 2 - this->menuSize.y +	pos.w
	);

	pRT->CreateSolidColorBrush(D2D1::ColorF(color), &this->pColorBrush);
}


MenuObject::~MenuObject()
{
	this->cleanUp();
}

void MenuObject::cleanUp()
{
	SafeRelease(&this->pColorBrush);
}

void MenuObject::addComponent(Component * component)
{
	this->components.push_back(component);
}

void MenuObject::render()
{
	pRT->FillRectangle(&this->rectangle, this->pColorBrush);
}
