#pragma
#ifndef CAMERA_H
#define CAMERA_H

#include "D3D.h"
#include "Locator.h"
#include <d3d11.h>
#include <DirectXMath.h>

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                     |
  |               CAMERA                |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

class Camera {
private:
	float			cameraMoveSpeed = 2.0f;
	float			cameraRotateSpeed = 0.02f;
	float			angle = 0.0f;
	float			nearPlane = 0.0f;
	float			farPlane = 0.0f;

	DirectX::XMFLOAT3 cameraStartPos;
	DirectX::XMFLOAT3 cameraStartFacingPos;
	DirectX::XMFLOAT3 cameraPos;
	DirectX::XMFLOAT3 cameraFacingDir;
	DirectX::XMFLOAT3 cameraUpDir;
	DirectX::XMFLOAT3 cameraRightDir;

	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
	//DirectX::XMMATRIX view;
	//DirectX::XMMATRIX projection;

	/// ---------- UPDATE-FUNCTION VARIABLES ---------
	// ------------- POSITION MOVEMENT ---------------
	DirectX::XMFLOAT3	upVecNormalized;
	DirectX::XMFLOAT3	moveVecNormalized;
	DirectX::XMFLOAT3	rightAxis;
	// _______________________________________________
	// --------------- LOOK-AT MOVEMENT --------------
	//float				rotationAngle;
	//DirectX::XMFLOAT3	rotationQuaternion;
	//bool				isMouseMovingUp;
	//DirectX::XMFLOAT3	newRotation_Float3;
	//DirectX::XMVECTOR	newRotation_Vector;
	//DirectX::XMFLOAT3	oldRotation_Float3;
	//DirectX::XMVECTOR	oldRotation_Vector;
	//DirectX::XMFLOAT3	tempRotationDifference_Float3;
	//DirectX::XMVECTOR	tempRotationDifference_Vector;
	// _______________________________________________
	///_______________________________________________

	bool updateRequired = false;

	void moveCameraUp();
	void moveCameraLeft();
	void moveCameraRight();
	void moveCameraForward();
	void moveCameraBackward();
	void updateRightDir();

	//void rotateCameraVertically(POINT mouseMovement);
	//void rotateCameraHorizontally(POINT mouseMovement);

public:
	void init(float arenaWidth, float arenaDepth);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Receives a 'characterMessage' of type 'TCHAR', which can result in:
	--- Camera Positional Movement: 'W', 'A', 'S', 'D', '32(SpaceBar)' = Up, 'R' = Reset Camera, 'H'.
	--- NOTE: See internal comment in regards to the 'H'.
	2. Receives 'mouseCoordinates' of type 'POINT', which can result in:
	--- Camera Rotational Movement: Y-Axis and/or X-Axis.
	3. Uses the 'updateRequired' bool to see if updating the Camera is necessary.
	--- Should an update be required, then the constant buffers will be edited here.
	*/
	void updateCamera();

	void resetCamera();

	void SETangle(float angleInput);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Converts the 'cameraPos' (XMVECTOR) to the XMFLOAT3 format.
	2. Stores the converted 'cameraPos' in 'cameraPos_Float3'.
	3. Returns 'cameraPos_Float3'.
	*/
	//DirectX::XMFLOAT3	GETcameraPosFloat3();
	//DirectX::XMVECTOR	GETcameraStartPos();
	DirectX::XMFLOAT3		GETcameraPos();
	DirectX::XMFLOAT3       GETfacingDir();
	DirectX::XMFLOAT4X4&	GETviewMatrix();
	DirectX::XMFLOAT4X4&	GETprojMatrix();
};

//______________________________________________//
//                                              //
//                END OF CAMERA                 //
//______________________________________________//
//////////////////////////////////////////////////

#endif
