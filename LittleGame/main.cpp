#include <Windows.h>
#include "D3D.h"
#include "GameManager.h"
#include "Locator.h"
#include <crtdbg.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameManager re;

	// Initialize window
	D3D::initializeWindow(hInstance, true, 1920, 1080, true);

	// Initialize DirectX
	D3D::initializeDirectX();

	// -------- TEST
	D3D::initializeDeferred();
	// -------- TEST

	// Initialize the game
	re.init(hInstance, nCmdShow);

	// Game loop
	while (re.getIsRunning()) {
		// Update delta time
		Locator::getGameTime()->UpdateFrameTime();
		// Handle events & update & render
		re.handleEvents();
		re.update();
		re.render();
	}

	re.cleanup();

	return 0;
}
