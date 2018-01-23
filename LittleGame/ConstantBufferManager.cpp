#include "D3D.h"
#include "ConstantBufferManager.h"
#include "Camera.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//             CONSTANT_BUFFER-RELATED CODE                /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

void editConstantBuffers(
	ID3D11Buffer*			targetBuffer,
	MatrixBufferPack		targetStruct,
	ID3D11DeviceContext*	*DeviceContext
) {

}

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//           END OF CONSTANT_BUFFER-RELATED CODE           \
////////////////////////////////////////////////////////////





//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                CONSTANT_BUFFER_MANAGER                  /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |      PRIVATE_FUNCTIONS      |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


void ConstantBufferManager::InitializeConstantMatrices()
{
	// WORLD MATRIX
	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();

	// PROJECTION MATRIX
	DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
		(DirectX::XM_PI * Camera::GETangle()),
		(D3D::getWidth() / D3D::getHeight()),
		Camera::GETnearPlane(),
		Camera::GETfarPlane()
	);

	// Below we provide the RAW MATRICES with data
	this->GETconstantBuffer()
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


ConstantBufferManager::ConstantBufferManager() {

}

ConstantBufferManager::~ConstantBufferManager() {

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
//             END OF CONSTANT_BUFFER_MANAGER              \
////////////////////////////////////////////////////////////