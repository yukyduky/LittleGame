#include "Locator.h"
#include "ConstantBufferManager.h"
#include "Camera.h"

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

void ConstantBufferManager::initialize() {
	this->initializeConstantMatrices();
	this->packageMatrices();
	this->createSetConstantBuffers();
	
	Locator::getD3D()->createConstantBuffer(&this->constantBuffer[CBTYPE::GEOOBJECT], sizeof(MatrixBufferPack));
}

void ConstantBufferManager::createSetConstantBuffers() {
	// CREATE BUFFER
	Locator::getD3D()->createConstantBuffer(&this->constantBuffer, sizeof(MatrixBufferPack));

	// SET BUFFER
	//(D3D::GETgDevCon())->VSSetConstantBuffers(0, 1, &this->ConstantBuffer);
	//(D3D::GETgDevCon())->PSSetConstantBuffers(0, 1, &this->ConstantBuffer);

	// Current GS-ConstantBuffer slots occupied:
	// 0 - 
	// 1 - 
	// 2 - 
	// ...
}

void ConstantBufferManager::calculateMatrices(DirectX::XMMATRIX& world) {
	this->rawMatrixData.worldView = &DirectX::XMMatrixMultiply(
		*this->rawMatrixData.world,
		*this->rawMatrixData.view
	);

	this->rawMatrixData.worldViewProj = &DirectX::XMMatrixMultiply(
		*this->rawMatrixData.worldView,
		*this->rawMatrixData.world
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


ConstantBufferManager::ConstantBufferManager() {
	//this->constantBuffer = nullptr;
	this->initialize();
}

ConstantBufferManager::~ConstantBufferManager() {

}

void ConstantBufferManager::editConstantBuffers(
	ID3D11Buffer* constantBuffer,
	void* targetStruct,
	size_t targetStructSize) {

	Locator::getD3D()->mapConstantBuffer(
		&constantBuffer,
		targetStruct,
		targetStructSize
	);
}

void ConstantBufferManager::releaseAll() {
	this->constantBuffer->Release();
}

MatrixBufferCalc* ConstantBufferManager::GETcalcMatrixData(DirectX::XMMATRIX& world) {
	this->calculateMatrices(world);
	return &this->rawMatrixData;
}

MatrixBufferPack*	ConstantBufferManager::GETpackagedMatrixData() {
	return &this->packagedMatrixData;
}

ID3D11Buffer* *ConstantBufferManager::GETconstantBuffer() {
	return &this->constantBuffer;
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