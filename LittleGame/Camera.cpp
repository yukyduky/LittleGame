#include "Camera.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//            START OF CAMERA-NCESSARY TOOLS               /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//


/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |      PRIVATE FUNCTIONS      |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


//_________________________________________//
//                                         //
//        END OF PRIVATE FUNCTIONS         //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |      PUBLIC FUNCTIONS       |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


//_________________________________________//
//                                         //
//         END OF PUBLIC FUNCTIONS         //
//_________________________________________//
/////////////////////////////////////////////






//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//              END OF CAMERA-NCESSARY TOOLS               \
////////////////////////////////////////////////////////////





//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                 START OF CAMERA CLASS                   /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//


ConstantBufferHandler::ConstantBufferHandler() {

}

ConstantBufferHandler::~ConstantBufferHandler() {

}





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |      PRIVATE FUNCTIONS      |
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
//        END OF PRIVATE FUNCTIONS         //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |      PUBLIC FUNCTIONS       |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

Camera::Camera() {

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

//_________________________________________//
//                                         //
//         END OF PUBLIC FUNCTIONS         //
//_________________________________________//
/////////////////////////////////////////////


//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                   END OF CAMERA CLASS                   \
////////////////////////////////////////////////////////////
