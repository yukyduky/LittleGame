#pragma
#ifndef CAMERA_H
#define CAMERA_H

#include <d3d11.h>
#include <DirectXMath.h>

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                     |
  |      CAMERA-NECESSARY TOOLS         |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

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

class ConstantBufferHandler {
private:

public:
	ConstantBufferHandler();
	~ConstantBufferHandler();

	void releaseAll();

	MatrixBufferPack	*GETpackagedMatrixData();
	ID3D11Buffer*		*GETconstantBuffer();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes... (SEE COMMENT AND CONTINUE FROM HERE)
	*/
	void Initialize(
		ID3D11Device*			*Device,
		ID3D11DeviceContext*	*DeviceContext
	);

};

//______________________________________________//
//                                              //
//        END OF CAMERA-NECESSARY TOOLS         //
//______________________________________________//
//////////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                     |
  |            CAMERA CLASS             |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

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
		MatrixBufferPack	*formattedStructData,
		ID3D11Buffer*		*GSconstantBuffer,
		ID3D11DeviceContext *deviceContext,
		bool				HoverCamActivationStatus
	);

	void resetCamera();

	DirectX::XMVECTOR GETcameraStartPos();
	DirectX::XMVECTOR GETcameraPosition();
	DirectX::XMVECTOR GETfacingDirection();
};

//______________________________________________//
//                                              //
//             END OF CAMERA CLASS              //
//______________________________________________//
//////////////////////////////////////////////////

#endif
