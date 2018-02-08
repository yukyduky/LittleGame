#pragma once
#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <d3d11.h>
#include <DirectXMath.h>

class MouseInput
{
public:
	MouseInput(DirectX::XMFLOAT3 cPos, DirectX::XMVECTOR cDir);
	~MouseInput();

	DirectX::XMFLOAT3 getWorldPosition();

private:
	//BITMAP mBitmap;
	DirectX::XMFLOAT3 cameraPos;
	DirectX::XMFLOAT3 cameraDirNor;
	DirectX::XMFLOAT2 mousePoint;
	POINT mPoint;

	DirectX::XMVECTOR surface;

	//XMPlaneFromPointNormal();

	bool check;

};



#endif // !MOUSEINPUT_H