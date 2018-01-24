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
	float cameraMoveSpeed = 2.0;
	float cameraRotateSpeed = 0.02;
	static float angle;
	static float nearPlane;
	static float farPlane;

	DirectX::XMFLOAT3 cameraPosFloat3;

	DirectX::XMVECTOR cameraStartPos = { 0, 10, -10 };
	DirectX::XMVECTOR cameraStartFacingDir = { 0, 0, 1 };
	DirectX::XMVECTOR cameraPos;
	DirectX::XMVECTOR cameraFacingDir;
	DirectX::XMVECTOR cameraUpDir;
	DirectX::XMVECTOR cameraRightDir;

	// --- UPDATE_VECTORS ---
	DirectX::XMVECTOR upVecNormalized;
	DirectX::XMVECTOR moveVecNormalized;
	DirectX::XMVECTOR rightAxis;

	DirectX::XMMATRIX view;

	bool updateRequired;
	void moveCameraUp();
	void moveCameraLeft();
	void moveCameraRight();
	void moveCameraForward();
	void moveCameraBackward();
	void updateRightDir();

	void rotateCameraVertically(POINT mouseMovement);
	void rotateCameraHorizontally(POINT mouseMovement);

public:
	Camera();
	~Camera();

	void updateCamera(
		TCHAR				characterMessage,
		POINT				mouseCoordinates,
		MatrixBufferPack	*formattedStructData,
		ID3D11Buffer*		*GSconstantBuffer,
		bool				HoverCamActivationStatus
	);

	void resetCamera();

	void				SETangle(float angleInput);

	DirectX::XMFLOAT3	GETcameraPosFloat3();
	DirectX::XMVECTOR	GETcameraStartPos();
	DirectX::XMVECTOR	GETcameraPos();
	DirectX::XMVECTOR	GETfacingDir();
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
