#pragma
#ifndef CAMERA_H
#define CAMERA_H

#include <d3d11.h>
#include <DirectXMath.h>

class Camera {
private:
	//float cameraMovementSpeed = 2.0;
	//float cameraRotationSpeed = 0.02;

	DirectX::XMVECTOR cameraStartPos = { 0, 10, -10 };
	DirectX::XMVECTOR cameraPosition;
	DirectX::XMVECTOR facingDirection;
	DirectX::XMVECTOR upDirection;
	DirectX::XMVECTOR rightDirection;
	DirectX::XMMATRIX view;

	void moveCameraUp();
	void moveCameraLeft();
	void moveCameraRight();
	void moveCameraForward();
	void moveCameraBackward();
	//void rotateCameraVertically(POINT MouseMovement);
	//void rotateCameraHorizontally(POINT MouseMovement);

	void updateRight();

public:
	Camera();
	~Camera();

	DirectX::XMVECTOR GETcameraStartPos();
	DirectX::XMVECTOR GETcameraPosition();
	DirectX::XMVECTOR GETfacingDirection();
};

#endif