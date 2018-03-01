#include "MenuObject.h"
#include "Locator.h"

MenuObject::MenuObject(size_t ID) : ID(ID)
{
	this->pRT = Locator::getD2D()->GETRenderTarget();
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

MenuObject::MenuObject(size_t ID, XMFLOAT4 pos, D2D1::ColorF color) : ID(ID)
{
	this->pRT = Locator::getD2D()->GETRenderTarget();
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

MenuObject::MenuObject(size_t ID, XMFLOAT4 pos, D2D1::ColorF color, const WCHAR * text) : ID(ID)
{
	this->pRT = Locator::getD2D()->GETRenderTarget();
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

	this->pRT->CreateSolidColorBrush(D2D1::ColorF(color), &this->pColorBrush);
	this->pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &this->pTextColorBrush);

	this->text = text;
}


MenuObject::~MenuObject()
{
	this->cleanUp();
}

void MenuObject::cleanUp()
{
	SafeRelease(&this->pColorBrush);
	SafeRelease(&this->pTextColorBrush);

}

void MenuObject::render()
{
	pRT->FillRectangle(&this->rectangle, this->pColorBrush);

	if (this->text)
	{
		//Renders the text ontop
		this->pRT->DrawText(
			this->text,
			wcslen(this->text),
			Locator::getD2D()->GETTextFormat(),
			this->rectangle,
			this->pTextColorBrush
		);
	}
}