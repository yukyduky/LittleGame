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
	float			cameraMoveSpeed = 2.0;
	float			cameraRotateSpeed = 0.02;
	static float	angle;
	static float	nearPlane;
	static float	farPlane;

	DirectX::XMFLOAT3 cameraPos_Float3;

	DirectX::XMVECTOR cameraStartPos = { 0, 10, -10 };
	DirectX::XMVECTOR cameraStartFacingDir = { 0, 0, 1 };
	DirectX::XMVECTOR cameraPos;
	DirectX::XMVECTOR cameraFacingDir;
	DirectX::XMVECTOR cameraUpDir;
	DirectX::XMVECTOR cameraRightDir;

	DirectX::XMMATRIX view;

	/// ---------- UPDATE-FUNCTION VARIABLES ---------
	// ------------- POSITION MOVEMENT ---------------
	DirectX::XMVECTOR	upVecNormalized;
	DirectX::XMVECTOR	moveVecNormalized;
	DirectX::XMVECTOR	rightAxis;
	// _______________________________________________
	// --------------- LOOK-AT MOVEMENT --------------
	float				rotationAngle;
	DirectX::XMVECTOR	rotationQuaternion;
	bool				isMouseMovingUp;
	DirectX::XMFLOAT3	newRotation_Float3;
	DirectX::XMVECTOR	newRotation_Vector;
	DirectX::XMFLOAT3	oldRotation_Float3;
	DirectX::XMVECTOR	oldRotation_Vector;
	DirectX::XMFLOAT3	tempRotationDifference_Float3;
	DirectX::XMVECTOR	tempRotationDifference_Vector;
	// _______________________________________________
	///_______________________________________________

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

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Receives a 'characterMessage' of type 'TCHAR', which can result in:
	--- Camera Positional Movement: 'W', 'A', 'S', 'D', '32(SpaceBar)' = Up, 'R' = Reset Camera, 'H'.
	--- NOTE: See internal comment in regards to the 'H'.
	2. Receives 'mouseCoordinates' of type 'POINT', which can result in:
	--- Camera Rotational Movement: Y-Axis and/or X-Axis.
	3. Uses the 'updateRequired' bool to see if updating the Camera is necessary.
	--- Should an update be required, then the constant buffers will be edited here.
	*/
	void updateCamera(
		TCHAR				characterMessage,
		POINT				mouseCoordinates,
		MatrixBufferPack	*formattedStructData,
		ID3D11Buffer*		*GSconstantBuffer,
		bool				HoverCamActivationStatus
	);

	void resetCamera();

	void SETangle(float angleInput);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Converts the 'cameraPos' (XMVECTOR) to the XMFLOAT3 format.
	2. Stores the converted 'cameraPos' in 'cameraPos_Float3'.
	3. Returns 'cameraPos_Float3'.
	*/
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
