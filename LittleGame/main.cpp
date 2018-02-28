#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include "ID3D.h"
#include "D3D.h"
#include <DirectXMath.h>

using namespace DirectX;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

void test();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtMemState s1;
	_CrtMemCheckpoint(&s1);
	// 7295 addComponent (AIComponent)
	// 258, 365, 380, 381 something in audiomanager
	// 1936 something with the quadtree initialization
	// 6054 something with KeyboardInput
	// 6063, 6074 something in KeyboardInput or InputComponent
	//	_CrtSetBreakAlloc(6114);
#endif

	test();

	ID3D* d3d = new D3D();
	Locator::provide(d3d);

	Locator::getD3D()->initializeWindow(hInstance, true, 1920, 1080, true);
	Locator::getD3D()->createSwapChain();

	GameManager gm;
	// Initialize the game
	gm.init(hInstance, nCmdShow);
	double deltaTime = 0.0;
	double timeLastFrame = 0.0;
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
			timeLastFrame = 0.0;
			OutputDebugStringA(msgbuf);
		}
	}

	gm.cleanUp();
	d3d->cleanup();
	delete d3d;

#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	_CrtMemDumpAllObjectsSince(&s1);
#endif
	return 0;
}

void test()
{
	XMVECTOR pos_W = XMVECTOR{ 100.0f, -0.5f, 800.0f };
	XMVECTOR camPos = XMVECTOR{ 800.0f, 1131.0f, 240.0f };
	XMVECTOR normal = XMVECTOR{ 0.0f, 1.0f, 0.0f };


	//if (pos_W.y == -0.5f) {
	XMVECTOR pToC = XMVectorSubtract(pos_W, camPos);
	pToC = XMVector3Normalize(pToC);

	XMVECTOR lDotN = XMVector3Dot(pToC, normal);
	//if (lDotN != 0.0f) {
		float i = 1.0f;
		bool intersected = false;
		XMVECTOR p = XMVECTOR{ 0.0f, 0.0f, 0.0f };
		int xGrid = 0;
		int yGrid = 0;

		do {
			XMFLOAT3 pos_Wfloat3;
			XMFLOAT3 pToCfloat3;
			XMStoreFloat3(&pos_Wfloat3, pos_W);
			XMStoreFloat3(&pToCfloat3, pToC);

			float pOnQuadX = pos_Wfloat3.x + pToCfloat3.x * (50 / 1.0f) * i; // gridDims.x / 2.0f stepsize
			float pOnQuadZ = pos_Wfloat3.z + pToCfloat3.z * (50 / 1.0f) * i;

			xGrid = (pOnQuadX - 0) / 50; // < MAX_NUM_FLOORGRIDS_X ? (pOnQuadX - gridStartPos.x) / gridDims.x : MAX_NUM_FLOORGRIDS_X - 1;
			yGrid = (pOnQuadZ - 0) / 50; // < MAX_NUM_FLOORGRIDS_Y ? (pOnQuadZ - gridStartPos.y) / gridDims.y : MAX_NUM_FLOORGRIDS_Y - 1;


			if (xGrid >= 0 && xGrid < 35 &&
				yGrid >= 0 && yGrid < 35) {
				XMVECTOR d = XMVectorDivide(XMVector3Dot(XMVectorSubtract(XMVECTOR{ pOnQuadX, -0.601f, pOnQuadZ }, camPos), normal), lDotN);

				p = XMVectorAdd((XMVectorMultiply(d, pToC)), camPos);

				XMFLOAT3 pfloat3;
				XMStoreFloat3(&pfloat3, p);


				if (pfloat3.x >= pOnQuadX && pfloat3.x <= pOnQuadX + 50 &&
					pfloat3.z >= pOnQuadZ && pfloat3.z <= pOnQuadZ + 50)
				{

					intersected = true;
					//diffuse = grid[xGrid][yGrid].color;
					//pos_W.y = p.y;
				}
			}
			else {
				intersected = true;
			}

			i += 1.0f;
		} while (!intersected);
		//	}
	//}
}