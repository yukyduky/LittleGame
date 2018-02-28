#include "RewardMenuState.h"
#include "GameManager.h"
#include "Button.h"
#include "StateManager.h"

RewardMenuState RewardMenuState::sRewardMenuState;

RewardMenuState * RewardMenuState::getInstance()
{
	return &sRewardMenuState;
}

void RewardMenuState::init()
{
	MenuState::init();

	this->displayMenu(this->initRewardMenu());
}

void RewardMenuState::handleEvents(GameManager * gm) {
	MSG msg;
	GLOBALMESSAGES globalmsg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed or the quit bool is true
		if (msg.message == WM_QUIT) {
			gm->quit();
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.wParam)
			{
			case VK_UP:
			case 0x57:
				this->currMenu->goUp(this->nrOfLoot);
				break;
			case VK_DOWN:
			case 0x53:
				this->currMenu->goDown(this->nrOfLoot);
				break;
			case VK_RETURN:
			case VK_SPACE:
				this->currMenu->pressButton();
				if (this->currMenu->GETCurrent()->GETBehavior() == BEHAVIOR::ADDGLYPH)
				{
					this->nrOfLoot--;
				}
				this->displayMenu(this->initRewardMenu());
				break;
			default:
				break;
			}
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	while (Locator::getGlobalEvents()->pollEvent(globalmsg)) {
		if (globalmsg == GLOBALMESSAGES::STARTGAME) {
			StateManager::changeState(GamePlayState::getInstance());
		}
		else if (globalmsg == GLOBALMESSAGES::RESUMEGAME) {
			StateManager::popState();
		}
	}
}


Menu * RewardMenuState::initRewardMenu()
{
	Menu* menu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	WCHAR* text = nullptr;
	int nextID;

	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(this->objD2D.GETRenderTarget(), nextID);
	menu->addQuad(object);

	nextID = this->newID();
	text = L"Next level";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100.0f,50.0f, 200.0f,150.0f }, D2D1::ColorF::GreenYellow,
		text, BEHAVIOR::REWSTARTGAME);
	menu->addButton(pButton);

	//Buttons
	XMFLOAT2 start{ 30.0f, 250.0f};

	if (this->nrOfLoot >= 1)
	{
		std::list<XMINT2> prev;

		for (int j = 0; j < 3; j++)
		{
			bool cpyFound = true;
			NAME name;
			GLYPHTYPE glyph;
			D2D1::ColorF color = D2D1::ColorF::WhiteSmoke;

			while (cpyFound)
			{
				name = (NAME)Locator::getRandomGenerator()->GenerateInt(0, (int)NAME::SIZE - 1);
				glyph = (GLYPHTYPE)Locator::getRandomGenerator()->GenerateInt(1, (int)GLYPHTYPE::SIZE - 1);

				cpyFound = false;
				for (auto &i : prev)
				{
					if (i.x == (int)name && i.y == (int)glyph)
					{
						cpyFound = true;
					}
				}
			}
			prev.push_back({ (int)name, (int)glyph });

			switch (name)
			{
			case NAME::AUTOATTACK:
				color = D2D1::ColorF::DarkGoldenrod;
				switch (glyph)
				{
				case GLYPHTYPE::NONE:
					text = L"AA NO";
					break;
				case GLYPHTYPE::GLYPH1:
					text = L"AA G1";
					break;
				case GLYPHTYPE::GLYPH2:
					text = L"AA G2";
					break;
				case GLYPHTYPE::GLYPH3:
					text = L"AA G3";
					break;
				default:
					text = L"ERROR";
					break;
				}
				break;
			case NAME::FIRE:
				color = D2D1::ColorF::OrangeRed;
				switch (glyph)
				{
				case GLYPHTYPE::NONE:
					text = L"Fr NO";
					break;
				case GLYPHTYPE::GLYPH1:
					text = L"Fr G1";
					break;
				case GLYPHTYPE::GLYPH2:
					text = L"Fr G2";
					break;
				case GLYPHTYPE::GLYPH3:
					text = L"Fr G3";
					break;
				default:
					text = L"ERROR";
					break;
				}
				break;
			case NAME::BOMB:
				color = D2D1::ColorF::DarkBlue;
				switch (glyph)
				{
				case GLYPHTYPE::NONE:
					text = L"Bom NO";
					break;
				case GLYPHTYPE::GLYPH1:
					text = L"Bom G1";
					break;
				case GLYPHTYPE::GLYPH2:
					text = L"Bom G2";
					break;
				case GLYPHTYPE::GLYPH3:
					text = L"Bom G3";
					break;
				default:
					text = L"ERROR";
					break;
				}
				break;
			case NAME::DASH:
				color = D2D1::ColorF::DarkOrange;
				switch (glyph)
				{
				case GLYPHTYPE::NONE:
					text = L"Dsh NO";
					break;
				case GLYPHTYPE::GLYPH1:
					text = L"Dsh G1";
					break;
				case GLYPHTYPE::GLYPH2:
					text = L"Dsh G2";
					break;
				case GLYPHTYPE::GLYPH3:
					text = L"Dsh G3";
					break;
				default:
					text = L"ERROR";
					break;
				}
				break;
			case NAME::BUFF:
				color = D2D1::ColorF::DarkCyan;
				switch (glyph)
				{
				case GLYPHTYPE::NONE:
					text = L"Buf NO";
					break;
				case GLYPHTYPE::GLYPH1:
					text = L"Buf G1";
					break;
				case GLYPHTYPE::GLYPH2:
					text = L"Buf G2";
					break;
				case GLYPHTYPE::GLYPH3:
					text = L"Buf G3";
					break;
				default:
					text = L"ERROR";
					break;
				}
				break;
			default:
				text = L"ERROR";
				color = D2D1::ColorF::WhiteSmoke;
				break;
			}

			pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, this->newID(),
				{ start.x,start.y, 100.0f,50.0f }, color,
				text, BEHAVIOR::ADDGLYPH,
				name, glyph);
			menu->addButton(pButton);

			start.x += 120.0f;
		}

		start.x = 30.0f;
		start.y += 70.0f;
	}

	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100.0f,start.y, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);


	//this->menus[MENUS::START] = menu;
	return menu;
}

void RewardMenuState::provide(ActorObject* player)
{
	this->player = player;
}

void RewardMenuState::startGame()
{
	this->player->switchSpell();
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::RESUMEGAME);
}
