#include "Camera.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                        CAMERA                           /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


void Camera::moveCameraUp() {
	// 'UP-movement' vector already exists, so we just copy + normalize it
	this->upVecNormalized = this->cameraUpDir;
	DirectX::XMVector3Normalize(this->upVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	this->upVecNormalized = DirectX::XMVectorScale(
		this->upVecNormalized,
		this->cameraMoveSpeed
	);

	// MOVE!!
	this->cameraPos = DirectX::XMVectorAdd(this->cameraPos, this->upVecNormalized);
}

void Camera::moveCameraLeft() {
	// Creates the 'LEFT-movement' vector
	this->moveVecNormalized = DirectX::XMVector3Cross(
		this->cameraFacingDir,
		this->cameraUpDir
	);

	// Normalize the vector
	DirectX::XMVector3Normalize(this->moveVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	this->moveVecNormalized = DirectX::XMVectorScale(
		this->moveVecNormalized,
		this->cameraMoveSpeed
	);

	// MOVE!!
	this->cameraPos = DirectX::XMVectorAdd(
		this->cameraPos,
		this->moveVecNormalized
	);
}

void Camera::moveCameraRight() {
	// Creates the 'RIGHT-movement' vector
	this->moveVecNormalized = DirectX::XMVector3Cross(
		this->cameraUpDir,
		this->cameraFacingDir
	);

	// Normalize the vector
	DirectX::XMVector3Normalize(this->moveVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	this->moveVecNormalized = DirectX::XMVectorScale(
		this->moveVecNormalized,
		this->cameraMoveSpeed
	);

	// MOVE!!
	this->cameraPos = DirectX::XMVectorAdd(this->cameraPos, this->moveVecNormalized);
}

void Camera::moveCameraForward() {
	// 'FORWARD-movement' vector already exists, so we just copy + normalize it
	this->moveVecNormalized = this->cameraFacingDir;
	DirectX::XMVector3Normalize(moveVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	this->moveVecNormalized = DirectX::XMVectorScale(
		this->moveVecNormalized,
		this->cameraMoveSpeed
	);

	// MOVE!!
	this->cameraPos = DirectX::XMVectorAdd(
		this->cameraPos,
		this->moveVecNormalized
	);
}

void Camera::moveCameraBackward() {
	// 'FORWARD-movement' vector already exists, so we just copy + normalize it
	this->moveVecNormalized = this->cameraFacingDir;
	DirectX::XMVector3Normalize(moveVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	// NOTE: We're scaling with NEGATIVE 'cameraMoveSpeed' to go backwards!!
	this->moveVecNormalized = DirectX::XMVectorScale(
		this->moveVecNormalized,
		(this->cameraMoveSpeed * -1)
	);

	// MOVE!!
	this->cameraPos = DirectX::XMVectorAdd(
		this->cameraPos,
		this->moveVecNormalized
	);
}

void Camera::updateRightDir() {
	this->cameraRightDir = DirectX::XMVector3Cross(
		this->cameraUpDir,
		this->cameraFacingDir
	);
}

void Camera::rotateCameraVertically(POINT mouseMovement) {

}

void Camera::rotateCameraHorizontally(POINT mouseMovemet) {

}

//_________________________________________//
//                                         //
//             END OF PRIVATE              //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PUBLIC            |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


Camera::Camera() {
	this->angle = 0.45;
	this->nearPlane = 0.5;
	this->farPlane = 200.0;

	this->updateRequired = false;

	this->cameraPos = this->cameraStartPos;
	this->cameraFacingDir = this->cameraStartFacingDir;
	this->cameraUpDir = { 0, 1, 0 };
}

Camera::~Camera() {

}

void Camera::updateCamera(
	TCHAR				characterMessage,
	POINT				mouseCoordinates,
	MatrixBufferPack	*packagedStructData,
	ID3D11Buffer*		*GSconstantBuffer,
	bool				HoverCamActivationStatus) {
	// POSITIONAL MOVEMENT
	if (characterMessage == 'W') {
		this->updateRequired = true;
		this->moveCameraForward();
	}
	else if (characterMessage == 'A') {
		this->updateRequired = true;
		this->moveCameraLeft();
	}
	else if (characterMessage == 'S') {
		this->updateRequired = true;
		this->moveCameraBackward();
	}
	else if (characterMessage == 'D') {
		this->updateRequired = true;
		this->moveCameraRight();
	}
	else if (characterMessage == 32) {	// 32 == Spacebar
		this->updateRequired = true;
		this->moveCameraUp();
	}
	else if (characterMessage == 'H')	// By-product of merging WindowsProcedure's handling of input and
		this->updateRequired = true;	// the attempt here.
										// -DanneBigD (November, 2016)

	// CAMERA ROTATION
	if (mouseCoordinates.y != 0) {
		this->updateRequired = true;
		this->rotateCameraVertically(mouseCoordinates);
	}

	if (mouseCoordinates.x != 0) {
		this->updateRequired = true;
		this->rotateCameraHorizontally(mouseCoordinates);
	}

	// MISC COMMANDS - Needs to be called after movement and rotation
	if (characterMessage == 'R') {
		updateRequired = true;
		this->resetCamera();
	}

	// IF 'updateRequired' = TRUE --> UPDATE
	if (updateRequired) {
		//Create new VIEW Matrix
		this->view = DirectX::XMMatrixLookToLH(
			this->cameraPos,
			this->cameraFacingDir,
			this->cameraUpDir
		);

		this->updateRightDir();

		// Updates the View Matrix in the PACKAGED Matrix Data
		DirectX::XMStoreFloat4x4(&packagedStructData->view, this->view);

		// Edit the constant buffers, updating VIEW data
		editConstantBuffers(*GSconstantBuffer, *packagedStructData);
	}
}

void Camera::resetCamera() {
	this->cameraPos = this->cameraStartPos;
	this->cameraFacingDir = { 0, 0, 1 };
	this->cameraUpDir = { 0, 1, 0 };
}

void Camera::SETangle(float angleInput) {
	this->angle = angleInput;
}

DirectX::XMFLOAT3 Camera::GETcameraPosFloat3() {
	DirectX::XMStoreFloat3(&this->cameraPosFloat3, this->cameraPos);
	return this->cameraPosFloat3;
}

DirectX::XMVECTOR Camera::GETcameraStartPos() {
	return this->cameraStartPos;
}

DirectX::XMVECTOR Camera::GETcameraPos() {
	return this->cameraPos;
}

DirectX::XMVECTOR Camera::GETfacingDir() {
	return this->cameraFacingDir;
}

float Camera::GETangle() {
	return angle;
}

float Camera::GETnearPlane() {
	return nearPlane;
}

float Camera::GETfarPlane() {
	return farPlane;
}

//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                      END OF CAMERA                      \
////////////////////////////////////////////////////////////
