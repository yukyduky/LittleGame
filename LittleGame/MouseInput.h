#pragma once
#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include <d3d11.h>
#include <DirectXMath.h>

class MouseInput
{
public:
	MouseInput(DirectX::XMFLOAT3 cPos, DirectX::XMFLOAT3 cDir);
	virtual ~MouseInput();

	// Returns the position that the mouse is in on in the plane of the player
	DirectX::XMFLOAT3 getWorldPosition();

private:
	DirectX::XMFLOAT3 cameraPos;
	DirectX::XMFLOAT3 cameraDirNor;
	DirectX::XMFLOAT2 mousePoint;
	POINT mPoint;

	DirectX::XMFLOAT4 surface;
};



#endif // !MOUSEINPUT_H