#pragma
#ifndef CAMERA_H
#define CAMERA_H

#include "D3D.h"
#include "ConstantBufferManager.h"
#include <d3d11.h>
#include <DirectXMath.h>

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                     |
  |               CAMERA                |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

class Camera {
private:
	//float cameraMovementSpeed = 2.0;
	//float cameraRotationSpeed = 0.02;
	static float angle;
	static float nearPlane;
	static float farPlane;

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

	void updateCamera(
		TCHAR				characterMessage,
		POINT				mouseCoordinates,
		MatrixBufferPack	*formattedStructData,
		ID3D11Buffer*		*GSconstantBuffer,
		ID3D11DeviceContext *deviceContext,
		bool				HoverCamActivationStatus
	);

	void resetCamera();

	void				SETangle(float angleInput);

	DirectX::XMVECTOR	GETcameraStartPos();
	DirectX::XMVECTOR	GETcameraPosition();
	DirectX::XMVECTOR	GETfacingDirection();
	static float		GETangle();
	static float		GETnearPlane();
	static float		GETfarPlane();
};

//______________________________________________//
//                                              //
//                END OF CAMERA                 //
//______________________________________________//
//////////////////////////////////////////////////

#endif
