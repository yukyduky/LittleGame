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
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


void ConstantBufferManager::InitializeConstantMatrices() {
	// Create the WORLD MATRIX
	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();

	// Create the PROJECTION MATRIX
	DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
		(DirectX::XM_PI * Camera::GETangle()),
		(D3D::getWidth() / D3D::getHeight()),
		Camera::GETnearPlane(),
		Camera::GETfarPlane()
	);

	// Below we provide the RAW MATRICES with data
	this->rawMatrixData.world = worldMatrix;
	this->rawMatrixData.projection = projectionMatrix;
}

void ConstantBufferManager::CreateSetConstantBuffers(
	ID3D11Device*			*Device,
	ID3D11DeviceContext*	*DeviceContext
) {
	// BUFFER DESCRIPTION ('Settings')
	D3D11_BUFFER_DESC cbDesc;
	memset(&cbDesc, 0, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(MatrixBufferPack);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;				// Needs to be DYNAMIC so that we can
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// Map/Unmap via 'editConstantBuffers()'.
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// SUBRESOURCE DATA ('Package' the data)
	D3D11_SUBRESOURCE_DATA InitData;
	memset(&InitData, 0, sizeof(InitData));
	InitData.pSysMem = &this->packagedMatrixData;	// Meant to recieve data - not create.
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// CREATE BUFFER
	(*Device)->CreateBuffer(&cbDesc, &InitData, &this->ConstantBuffer);

	// SET BUFFER
	(*DeviceContext)->VSSetConstantBuffers(0, 1, &this->ConstantBuffer);
	(*DeviceContext)->GSSetConstantBuffers(0, 1, &this->ConstantBuffer);
	(*DeviceContext)->PSSetConstantBuffers(0, 1, &this->ConstantBuffer);

	// Current GS-ConstantBuffer slots occupied:
	// 0 - 
	// 1 - 
	// 2 - 
	// ...
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


ConstantBufferManager::ConstantBufferManager() {
	this->ConstantBuffer = nullptr;
}

ConstantBufferManager::~ConstantBufferManager() {

}

void ConstantBufferManager::Initialize(
	ID3D11Device*			*Device,
	ID3D11DeviceContext*	*DeviceContext
) {
	this->InitializeConstantMatrices();
	this->packageMatrices();
	this->CreateSetConstantBuffers(
		Device,
		DeviceContext
	);
}

void ConstantBufferManager::releaseAll() {
	this->ConstantBuffer->Release();
}

MatrixBufferPack *ConstantBufferManager::GETpackagedMatrixData() {
	return &this->packagedMatrixData;
}

ID3D11Buffer* *ConstantBufferManager::GETconstantBuffer() {
	return &this->ConstantBuffer;
}

//_________________________________________//
//                                         //
//             END OF PUBLIC               //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//             END OF CONSTANT_BUFFER_MANAGER              \
////////////////////////////////////////////////////////////