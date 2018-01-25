#include "D3D.h"
#include "ConstantBufferManager.h"
#include "Camera.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                             CONSTANT_BUFFER-RELATED CODE        /
///////////////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

void editConstantBuffers(
	ID3D11Buffer*			targetBuffer,
	MatrixBufferPack		targetStruct
) {
	D3D11_MAPPED_SUBRESOURCE MappedBuffer;

	D3D::GETgDevCon()->Map(targetBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedBuffer);
	memcpy(MappedBuffer.pData, &targetStruct, sizeof(targetStruct));
	D3D::GETgDevCon()->Unmap(targetBuffer, 0);
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

void ConstantBufferManager::CreateSetConstantBuffers() {
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
	(D3D::GETgDevice())->CreateBuffer(&cbDesc, &InitData, &this->ConstantBuffer);

	// SET BUFFER
	(D3D::GETgDevCon())->VSSetConstantBuffers(0, 1, &this->ConstantBuffer);
	(D3D::GETgDevCon())->GSSetConstantBuffers(0, 1, &this->ConstantBuffer);
	(D3D::GETgDevCon())->PSSetConstantBuffers(0, 1, &this->ConstantBuffer);

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

void ConstantBufferManager::Initialize() {
	this->InitializeConstantMatrices();
	this->packageMatrices();
	this->CreateSetConstantBuffers();
}

void ConstantBufferManager::packageMatrices() {
	DirectX::XMStoreFloat4x4(&this->packagedMatrixData.world, this->rawMatrixData.world);
	DirectX::XMStoreFloat4x4(&this->packagedMatrixData.view, this->rawMatrixData.view);
	DirectX::XMStoreFloat4x4(&this->packagedMatrixData.projection, this->rawMatrixData.projection);
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
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                              END OF CONSTANT_BUFFER_MANAGER      \
/////////////////////////////////////////////////////////////////////