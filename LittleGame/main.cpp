#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include "ID3D.h"
#include "D3D.h"




int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(323); // 1134 1133 1132

	ID3D* d3d = new D3D();
	Locator::provide(d3d);

	Locator::getD3D()->initializeWindow(hInstance, true, 800, 600, true);
	Locator::getD3D()->createSwapChain();

	GameManager gm;
	// Initialize the game
	gm.init(hInstance, nCmdShow);
	double deltaTime;
	double timeLastFrame = 0;
	int frames = 0;
	char msgbuf[20];

	// Game loop
	while (gm.getIsRunning()) {
		// Update delta time
		Locator::getGameTime()->UpdateFrameTime();
		deltaTime = Locator::getGameTime()->getDeltaTime();
		timeLastFrame += deltaTime * 1000;
		
		// Handle events & update & render
		gm.handleEvents();
		gm.update();
		gm.render();
		frames++;

		if (timeLastFrame > 1000.0) {
			sprintf_s(msgbuf, "FPS: %d\n", frames);
			frames = 0;
			timeLastFrame = 0;
			OutputDebugStringA(msgbuf);
		}

	}
	gm.cleanup();
	d3d->cleanup();
	delete d3d;

	return 0;
}
