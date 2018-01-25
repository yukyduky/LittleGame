#include "Camera.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                              CAMERA                   /
/////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

/// INITIALIZING STATIC VALUES ('GLOBALS')
float Camera::angle = 0.45;
float Camera::nearPlane = 0.5;
float Camera::farPlane = 200.0;





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
	// Create & set the new 'Right' vector
	this->cameraRightDir = DirectX::XMVector3Cross(
		this->cameraUpDir,
		this->cameraFacingDir
	);
}

void Camera::rotateCameraVertically(POINT mouseMovement) {
	// Create the 'Right' vector
	this->rightAxis = DirectX::XMVector3Cross(
		this->cameraUpDir,
		this->cameraFacingDir
	);

	// Update the 'rotationAngle' based on the 'cameraRotateSpeed'
	this->rotationAngle = mouseMovement.y * cameraRotateSpeed;

	// Create the Quaternion using the 'Right' vector + 'rotationAngle'
	this->rotationQuaternion = DirectX::XMQuaternionRotationAxis(
		this->rightAxis,
		this->rotationAngle
	);

	/// Camera-Plane movement is currently turned OFF. Un-comment the line below to turn it ON.
	///this->cameraUpDir = DirectX::XMVector3Rotate(this->cameraUpDir, this->rotationQuaternion);

	// SIMPLY EXPLAINED: If 'mouseMovement.y' is negative; the mouse was moved upwards,
	// resulting in 'TRUE'. Else 'moveMovement.y' is positive; the mouse was moved downwards,
	// resulting in 'FALSE'.
	this->isMouseMovingUp = (mouseMovement.y < 0);

	// Create the direction the camera is facing (VECTOR form)
	this->newRotation_Vector = DirectX::XMVector3Rotate(
		this->cameraFacingDir,
		this->rotationQuaternion
	);

	// Convert & Store 'newRotation' (VECTOR --> FLOAT3)
	DirectX::XMStoreFloat3(
		&this->newRotation_Float3,
		this->newRotation_Vector
	);

	// Convert & Store 'oldRotation' (VECTOR --> FLOAT3)
	// NOTE: 'oldRotation' based off of previous 'cameraFacingDir'
	DirectX::XMStoreFloat3(
		&this->oldRotation_Float3,
		this->cameraFacingDir
	);

	// Create a temporary XMVECTOR for the difference in 'z-value'
	// (New  vs. Old)
	this->tempRotationDifference_Vector = DirectX::XMVector3Dot(
		DirectX::XMVECTOR{ 0, 0, this->newRotation_Float3.z },
		DirectX::XMVECTOR{ 0, 0, this->oldRotation_Float3.z }
	);

	// Convert temp XMVECTOR to XMFLOAT3
	DirectX::XMStoreFloat3(
		&this->tempRotationDifference_Float3,
		this->tempRotationDifference_Vector
	);

	// Likely that this combats the 'look-too-far-up-or-down' problem.
	// Ask Danne or Oliver for further info.
	if (this->tempRotationDifference_Float3.x > 0) {

		if (this->isMouseMovingUp) {
			if (this->newRotation_Float3.y > this->oldRotation_Float3.y) {
				// Set the new direction for the camera
				this->cameraFacingDir = this->newRotation_Vector;
			}
		}

		else {
			if (this->newRotation_Float3.y < this->oldRotation_Float3.y) {
				// Set the new direction for the camera
				this->cameraFacingDir = this->newRotation_Vector;
			}
		}
	}
}

void Camera::rotateCameraHorizontally(POINT mouseMovement) {
	// Update the 'rotationAngle' based on the 'cameraRotateSpeed'
	this->rotationAngle = (mouseMovement.x * cameraRotateSpeed);

	// Create the Quaternion using the 'Right' vector + 'rotationAngle'
	this->rotationQuaternion = DirectX::XMQuaternionRotationAxis(
		this->cameraUpDir,
		this->rotationAngle
	);

	/// Camera-Plane movement is currently turned OFF. Un-comment the line below to turn it ON.
	///this->cameraUpDir = DirectX::XMVector3Rotate(this->cameraUpDir, this->rotationQuaternion);

	// Create & set the direction the camera is facing
	this->cameraFacingDir = DirectX::XMVector3Rotate(
		this->cameraFacingDir,
		this->rotationQuaternion
	);
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
	DirectX::XMStoreFloat3(&this->cameraPos_Float3, this->cameraPos);
	return this->cameraPos_Float3;
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
//                             END OF CAMERA               \
////////////////////////////////////////////////////////////
