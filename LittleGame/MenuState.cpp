#include "MenuState.h"
#include "GamePlayState.h"
#include "MenuPauseState.h"
#include "HomeMenuState.h"
#include "MenuStatisticsState.h"
#include "GameManager.h"
#include "Locator.h"
#include "StateManager.h"
#include <SimpleMath.h>
#include <DirectXMath.h>


using namespace DirectX::SimpleMath;

void MenuState::init() 
{
}

void MenuState::cleanUp()
{
	this->currMenu->cleanUp();

	for (auto &i : this->menuObjects)
	{
		i->cleanUp();
		delete i;
	}
	this->menuObjects.clear();

	this->ID = 0;
}

void MenuState::pause() {

}

void MenuState::resume()
{
}

void MenuState::handleEvents(GameManager * gm) {
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
				this->currMenu->goUp();
				break;
			case VK_DOWN:
			case 0x53:
				this->currMenu->goDown();
				break;
			case VK_RETURN:
			case VK_SPACE:
				this->currMenu->pressButton();
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
			Locator::getD2D()->closeMenu();
		}
		else if (globalmsg == GLOBALMESSAGES::RESUMEGAME) {
			StateManager::popState();
			Locator::getD2D()->closeMenu();
		}
		else if (globalmsg == GLOBALMESSAGES::RESTARTGAME) {
			Locator::getStatsHeader()->resetStats();

			StateManager::changeState(HomeMenuState::getInstance());
			//StateManager::changeState(GamePlayState::getInstance());
			//StateManager::pushState(PauseMenuState::getInstance());
		}
	}
}


void MenuState::update(GameManager * gm)
{
	if (this->quit)
	{
		gm->quit();
	}
}

void MenuState::render(GameManager * gm) {
	Locator::getD2D()->OnRender(this->menuObjects);
}

std::wstring MenuState::intToWchar(int input)
{
	std::wstring texten = std::to_wstring(input);
	return texten;
}

void MenuState::addLoadOut(Menu * menu)
{
	WCHAR* text = nullptr;
	std::wstring textStr;
	D2D1::ColorF color = D2D1::ColorF::WhiteSmoke;
	MenuObject* object = nullptr;

	for (int i = 0; i < 5; i++)
	{
		int glyph = Locator::getStatsHeader()->getStats().glyphs[i];
		switch (i)
		{
		case 0: //NAME::AUTOATTACK:
			color = D2D1::ColorF::DarkGoldenrod;
			switch (glyph)
			{
			case 0: //GLYPHTYPE::NONE:
				text = L"AutoA NO";
				break;
			case 1: // GLYPHTYPE::GLYPH1:
				text = L"AutoA \n Tripple-burst";
				break;
			case 2: // GLYPHTYPE::GLYPH2:
				text = L"AutoA \n Sniper";
				break;
			case 3: // GLYPHTYPE::GLYPH3:
				text = L"AutoA \n Firerate";
				break;
			default:
				text = L"ERROR";
				break;
			}
			break;
		case 1: //NAME::FIRE:
			color = D2D1::ColorF::Orchid;
			switch (glyph)
			{
			case 0: //GLYPHTYPE::NONE:
				text = L"Fire NO";
				break;
			case 1: // GLYPHTYPE::GLYPH1:
				text = L"Fire \n Flamethrower";
				break;
			case 2: // GLYPHTYPE::GLYPH2:
				text = L"Fire \n Enlarge";
				break;
			case 3: // GLYPHTYPE::GLYPH3:
				text = L"Fire \n Railgun";
				break;
			default:
				text = L"ERROR";
				break;
			}
			break;
		case 2: //NAME::BOMB:
			color = D2D1::ColorF::Gray;
			switch (glyph)
			{
			case 0: //GLYPHTYPE::NONE:
				text = L"Bomb NO";
				break;
			case 1: // GLYPHTYPE::GLYPH1:
				text = L"Bomb \n Splinter Bomb";
				break;
			case 2: // GLYPHTYPE::GLYPH2:
				text = L"Bomb \n Mine";
				break;
			case 3: // GLYPHTYPE::GLYPH3:
				text = L"Bomb \n Black-hole";
				break;
			default:
				text = L"ERROR";
				break;
			}
			break;
		case 3: //NAME::DASH:
			color = D2D1::ColorF::Orange;
			switch (glyph)
			{
			case 0: //GLYPHTYPE::NONE:
				text = L"Dash NO";
				break;
			case 1: // GLYPHTYPE::GLYPH1:
				text = L"Dash \n Retreat";
				break;
			case 2: // GLYPHTYPE::GLYPH2:
				text = L"Dash \n Long-dash";
				break;
			case 3: // GLYPHTYPE::GLYPH3:
				text = L"Dash \n Everlasting";
				break;
			default:
				text = L"ERROR";
				break;
			}
			break;
		case 4: //NAME::BUFF:
			color = D2D1::ColorF::RoyalBlue;
			switch (glyph)
			{
			case 0: //GLYPHTYPE::NONE:
				text = L"Buff NO";
				break;
			case 1: // GLYPHTYPE::GLYPH1:
				text = L"Buff \n Berserk-mode";
				break;
			case 2: // GLYPHTYPE::GLYPH2:
				text = L"Buff \n Fear";
				break;
			case 3: // GLYPHTYPE::GLYPH3:
				text = L"Buff \n Keep Speed";
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

		
		//Glyph desc
		object = new MenuObject(this->newID(),
			{ -600.0f, i * 110.0f, 200.0f,100.0f }, color,
			text);
		menu->addQuad(object);

	}

	color = D2D1::ColorF::DarkSlateGray;
	for (int eneUpg = 0; eneUpg < (int)ENEMYUPGRADE::SIZE; eneUpg++)
	{
		switch ((ENEMYUPGRADE)eneUpg)
		{
		case ENEMYUPGRADE::DAMAGE:
			textStr = L"Damage: " + std::to_wstring(Locator::getStatsHeader()->getStats().enemyUpg[eneUpg]);
			break;
		case ENEMYUPGRADE::HEALTH:
			textStr = L"Health: " + std::to_wstring(Locator::getStatsHeader()->getStats().enemyUpg[eneUpg]);
			break;
		case ENEMYUPGRADE::AMOUNT:
			textStr = L"Amount: " + std::to_wstring(Locator::getStatsHeader()->getStats().enemyUpg[eneUpg]);
			break;
		case ENEMYUPGRADE::SPEED:
			textStr = L"Speed: " + std::to_wstring(Locator::getStatsHeader()->getStats().enemyUpg[eneUpg]);
			break;
		default:
			textStr = L"ERROR";
			break;
		}

		//Glyph desc
		object = new MenuObject(this->newID(),
			{ -250.0f, eneUpg * 110.0f, 100.0f,100.0f }, color,
			textStr);
		menu->addQuad(object);
	}
	

}

WCHAR * MenuState::getCurrSpellText(NAME name)
{
	WCHAR* text = nullptr;
	D2D1::ColorF color = D2D1::ColorF::WhiteSmoke;
	int glyph = Locator::getStatsHeader()->getStats().glyphs[(int)name];

	switch ((int)name)
	{
	case 0: //NAME::AUTOATTACK:
		color = D2D1::ColorF::DarkGoldenrod;
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"AutoA NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"AutoA \n Tripple-burst";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"AutoA \n Sniper";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"AutoA \n Firerate";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	case 1: //NAME::FIRE:
		color = D2D1::ColorF::OrangeRed;
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"Fire NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"Fire \n Flamethrower";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"Fire \n Enlarge";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"Fire \n Railgun";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	case 2: //NAME::BOMB:
		color = D2D1::ColorF::DarkBlue;
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"Bomb NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"Bomb \n Splinter Bomb";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"Bomb \n Mine";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"Bomb \n Black-hole";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	case 3: //NAME::DASH:
		color = D2D1::ColorF::DarkOrange;
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"Dash NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"Dash \n Retreat";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"Dash \n Long-dash";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"Dash \n Everlasting";
			break;
		default:
			text = L"ERROR";
			break;
		}
		break;
	case 4: //NAME::BUFF:
		color = D2D1::ColorF::DarkCyan;
		switch (glyph)
		{
		case 0: //GLYPHTYPE::NONE:
			text = L"Buff NO";
			break;
		case 1: // GLYPHTYPE::GLYPH1:
			text = L"Buff \n Berserk-mode";
			break;
		case 2: // GLYPHTYPE::GLYPH2:
			text = L"Buff \n Fear";
			break;
		case 3: // GLYPHTYPE::GLYPH3:
			text = L"Buff \n Keep Speed";
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

	return text;
}

void MenuState::displayMenu(Menu* menu)
{
	for (auto &i : this->menuObjects)
	{
		i->cleanUp();
		delete i;
	}
	this->menuObjects.clear();

	if (this->currMenu)
	{
		this->currMenu->cleanUp();
	}

	this->currMenu = menu;
	for (auto &i : this->currMenu->getObjects())
	{
		this->menuObjects.push_back(i);
	}
}

void MenuState::startGame()
{
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::STARTGAME);
}

void MenuState::resumeGame()
{
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::RESUMEGAME);
}

void MenuState::restartGame()
{
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::RESTARTGAME);
}

void MenuState::statsWindow()
{
	StateManager::popState();
	StateManager::changeState(MenuStatisticsState::getInstance());
}

