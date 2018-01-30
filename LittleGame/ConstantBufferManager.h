#pragma
#ifndef CONSTANTBUFFERMANAGER_H
#define CONSTANTBUFFERMANAGER_H

#include "IConstantBufferManager.h"
#include "D3D.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <array>





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                       |
  |       CONSTANT_BUFFER_MANAGER         |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

class ConstantBufferManager : public IConstantBufferManager {
private:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes the Constant Buffer Manager by:
	--- Initializing the Constant Matrices.
	--- 'Packaging' said Constant Matrices into a '4x4' format.
	--- Create the Constant Buffer (D3D11_BUFFER_DESC & D3D11_SUBRESOURCE_DATA).
	*/
	void initialize();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creating and Setting the ConstantBuffer by:
	--- Defining the settings (D3D11_BUFFER_DESC).
	--- 'Packaging'/'Initiating' the data (D3D11_SUBRESOURCE_DATA).
	--- Creating the buffer via D3D-Device (Device->CreateBuffer()).
	--- Set the buffer (decide which shader should have access to the buffer).
	*/
	void createSetConstantBuffers();

	void calculateMatrices(DirectX::XMMATRIX& world);

public:
	ConstantBufferManager();
	~ConstantBufferManager();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. NON-CLASS FUNCTION.
	2. Allows us to edit the data within the Constant Buffers.
	--- DeviceContext()->Map() 'opens' the ID3D11Buffer for writing.
	--- 'memcpy' copies the data from our already packaged MatrixBufferPack.
	--- DeviceContext()->Unmap() 'closes' the ID3D11Buffer.
	*/
	void editConstantBuffers(ID3D11Buffer* constantBuffer, void* targetStruct, size_t targetStructSize);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calls 'this->ConstantBuffer->Release()'.
	2. ConstantBuffer is of the 'ID3D11Buffer' type.
	*/
	void releaseAll();
};

//______________________________________________//
//                                              //
//        END OF CONSTANT_BUFFER_MANAGER        //
//______________________________________________//
//////////////////////////////////////////////////

#endif