#pragma
#ifndef CAMERA_H
#define CAMERA_H

#include <d3d11.h>
#include <DirectXMath.h>

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |										|
  |		 CAMERA-NECESSARY TOOLS			|
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

class ConstantBuffer {
private:
	struct MatrixBufferCalc {
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	struct MatrixBufferPack {
		DirectX::XMFLOAT4X4 world;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;

		DirectX::XMFLOAT4 Kd;
		DirectX::XMFLOAT4 ColorID;
	};



public:
	ConstantBuffer();
	~ConstantBuffer();

};

//______________________________________________//
//											    //
//        END OF CAMERA-NECESSARY TOOLS         //
//______________________________________________//
//////////////////////////////////////////////////





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

	void updateCamera(
		TCHAR				characterMessage,
		POINT				mouseCoordinates,
		MatrixBufferStored	*formattedStructData,
		ID3D11Buffer*		*GSconstantBuffer,
		ID3D11DeviceContext *deviceContext,
		bool				HoverCamActivationStatus
	);

	void resetCamera();

	DirectX::XMVECTOR GETcameraStartPos();
	DirectX::XMVECTOR GETcameraPosition();
	DirectX::XMVECTOR GETfacingDirection();
};

#endif