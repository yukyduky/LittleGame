#include "Button.h"
#include "MenuState.h"

Button::Button(size_t ID, XMFLOAT3 pos, BEHAVIOR behavior) : MenuObject(ID, pos)
{
	this->behavior = behavior;
	this->pMS = nullptr;
}

Button::Button(size_t ID, XMFLOAT3 pos, BEHAVIOR behavior, MenuState* pMS) : MenuObject(ID, pos)
{
	this->behavior = behavior;
	this->pMS = pMS;
	this->nextButton = this;
	this->prevButton = this;
}

Button::~Button()
{
}

void Button::onPress()
{
	switch (this->behavior)
	{
	case BEHAVIOR::GOSTART:
		this->pMS->displayMenu(MENUS::START);
		break;
	case BEHAVIOR::GOOPTIONS:
		this->pMS->displayMenu(MENUS::OPTIONS);
		break;
	default:
		break;
	}
}
