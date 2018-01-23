#include "Camera.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                        CAMERA                           /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

ConstantBufferManager::ConstantBufferManager() {

}

ConstantBufferManager::~ConstantBufferManager() {

}





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |      PRIVATE_FUNCTIONS      |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


void Camera::moveCameraUp() {

}

void Camera::moveCameraLeft() {

}

void Camera::moveCameraRight() {

}

void Camera::moveCameraForward() {

}

void Camera::moveCameraBackward() {

}

void Camera::updateRight() {

}

//_________________________________________//
//                                         //
//        END OF PRIVATE_FUNCTIONS         //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |      PUBLIC_FUNCTIONS       |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


Camera::Camera() {
	this->angle = 0.45;
	this->nearPlane = 0.5;
	this->farPlane = 200.0;
}

Camera::~Camera() {

}

void Camera::updateCamera(
	TCHAR				characterMessage,
	POINT				mouseCoordinates,
	MatrixBufferPack	*formattedStructData,
	ID3D11Buffer*		*GSconstantBuffer,
	ID3D11DeviceContext *deviceContext,
	bool				HoverCamActivationStatus) {

}

void Camera::resetCamera() {

}

void Camera::SETangle(float angleInput) {
	this->angle = angleInput;
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
//         END OF PUBLIC_FUNCTIONS         //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                      END OF CAMERA                      \
////////////////////////////////////////////////////////////
