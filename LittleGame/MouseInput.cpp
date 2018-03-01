#include "MouseInput.h"
#include "Locator.h"
#include "ArenaGlobals.h"

MouseInput::MouseInput(DirectX::XMFLOAT3 cPos, DirectX::XMFLOAT3 cDir)
{
	DirectX::XMFLOAT3 direction;

	this->cameraPos = cPos;
	DirectX::XMVECTOR tempPos = DirectX::XMLoadFloat3(&cPos);
	DirectX::XMVECTOR tempDir = DirectX::XMLoadFloat3(&cDir);

	DirectX::XMVECTOR dir = DirectX::XMVectorSubtract(tempDir, tempPos);

	dir = DirectX::XMVector3Normalize(dir);

	// a plane on hte same height as the middel of the player
	this->surface = { 0.0f, 1.0f, 0.0f, -40.f };

	DirectX::XMStoreFloat3(&direction, dir);
	this->cameraDirNor = cDir;
}

MouseInput::~MouseInput()
{
}

DirectX::XMFLOAT3 MouseInput::getWorldPosition()
{
	DirectX::XMFLOAT3 result;

	// Takes the position (in pixels) of the cursor in hte whole screen
	GetCursorPos(&this->mPoint);
	// Converts it to the pixels in the window
	ScreenToClient(Locator::getD3D()->GEThwnd(), &this->mPoint);

	//(0,0)-------(wX,0)
	//  |			|
	//  |			|
	//  |			|
	//(0,wY)-----(wX,wY)


	this->mousePoint.x = static_cast<float>(this->mPoint.x);
	this->mousePoint.y = static_cast<float>(this->mPoint.y);
	
	size_t wWid = Locator::getD3D()->GETwWidth();
	size_t wHei = Locator::getD3D()->GETwHeight();

	this->mousePoint.x = ((2 * mousePoint.x) / wWid) - 1.0f;
	this->mousePoint.y = ((2 * mousePoint.y) / wHei) - 1.0f;

	DirectX::XMFLOAT3 vecX(1, 0, 0);
	DirectX::XMFLOAT3 vecY(0, -1.0f * this->cameraDirNor.z, this->cameraDirNor.y);

	DirectX::XMFLOAT3 vecO(this->cameraPos.x + this->cameraDirNor.x, this->cameraPos.y + this->cameraDirNor.y, this->cameraPos.z + this->cameraDirNor.z);

	// the cursors position in world cordinates
	DirectX::XMFLOAT3 pointP(
		vecO.x + mousePoint.x,
		vecO.y + mousePoint.y * vecY.y,
		vecO.z + mousePoint.y * vecY.z);

	DirectX::XMVECTOR vecP = DirectX::XMLoadFloat3(&pointP);
	DirectX::XMVECTOR vecCam = DirectX::XMLoadFloat3(&this->cameraPos);

	DirectX::XMVECTOR vecPointInArena;
	DirectX::XMVECTOR surfaceVector = DirectX::XMLoadFloat4(&this->surface);
	vecPointInArena = DirectX::XMPlaneIntersectLine(surfaceVector, vecP, vecCam);

	DirectX::XMStoreFloat3(&result, vecPointInArena);

	return result;
}
