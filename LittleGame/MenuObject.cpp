#include "MenuObject.h"
#include "Component.h"

MenuObject::MenuObject(ID2D1HwndRenderTarget* RT, size_t ID) : ID(ID), pRT(RT)
{
	this->menuSize = { 200.0f, 400.0f, 300.0f };
	//Default background
	D2D1_SIZE_F rtSize = pRT->GetSize();
	this->pos = {
		(rtSize.width / 2) - this->menuSize.x + this->menuSize.z,
		(rtSize.height / 2) - this->menuSize.y
	};
	this->size = {
		this->menuSize.x * 2,
		this->menuSize.y * 2
	};

	this->rectangle = D2D1::RectF(
		this->pos.x,
		this->pos.y,
		this->pos.x + this->size.x,
		this->pos.y + this->size.y
	);

	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkMagenta), &this->pColorBrush);
}

MenuObject::MenuObject(ID2D1HwndRenderTarget* RT ,size_t ID, XMFLOAT4 pos, D2D1::ColorF color) : ID(ID), pRT(RT)
{
	this->menuSize = { 200.0f, 400.0f, 300.0f };
	D2D1_SIZE_F rtSize = pRT->GetSize();
	this->pos = {
		rtSize.width / 2 - this->menuSize.x + this->menuSize.z + pos.x,
		rtSize.height / 2 - this->menuSize.y + pos.y
	};
	this->size = {
		pos.z,
		pos.w
	};

	this->rectangle = D2D1::RectF(
		this->pos.x,
		this->pos.y,
		this->pos.x + this->size.x,
		this->pos.y + this->size.y
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