#include <Windows.h>
#include "D3D.h"
#include "GameManager.h"
#include "Locator.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	GameManager re;

	// Initialize window
	D3D::initializeWindow(hInstance, true, 1920, 1080, true);

	// Initialize DirectX
	D3D::initializeDirectX();

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

	// Cleanup the game
	re.cleanup();

	return 0;
}
