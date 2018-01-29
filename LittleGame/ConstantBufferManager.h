#pragma
#ifndef CONSTANTBUFFERMANAGER_H
#define CONSTANTBUFFERMANAGER_H

#include "D3D.h"
#include <d3d11.h>
#include <DirectXMath.h>

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                           |
  |       CONSTANT_BUFFER-RELATED CODE        |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/


// While in this format, we perform matrix-manipulation using DirectX functions.
struct MatrixBufferCalc {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
};

// This is the 'packaged' format of the matrices, which we send to the shaders.
struct MatrixBufferPack {
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;

	DirectX::XMFLOAT4 Kd;
	DirectX::XMFLOAT4 ColorID;
};

// NON-CLASS FUNCTION: Allows us to alter the data within the Constant Buffers.
/*- - - - - - - -<INFORMATION>- - - - - - - -
1. NON-CLASS FUNCTION.
2. Allows us to edit the data within the Constant Buffers.
--- DeviceContext()->Map() 'opens' the ID3D11Buffer for writing.
--- 'memcpy' copies the data from our already packaged MatrixBufferPack.
--- DeviceContext()->Unmap() 'closes' the ID3D11Buffer.
*/
void editConstantBuffers(
	ID3D11Buffer*			targetBuffer,
	MatrixBufferPack		targetStruct
);

//__________________________________________________//
//                                                  //
//        END OF CONSTANT_BUFFER-RELATED CODE       //
//__________________________________________________//
//////////////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                                       |
  |       CONSTANT_BUFFER_MANAGER         |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

class ConstantBufferManager {
private:
	MatrixBufferCalc	rawMatrixData;
	MatrixBufferPack	packagedMatrixData;
	ID3D11Buffer*		ConstantBuffer;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes the WORLD & PROJECTION matrices.
	2. Matrices are initialized in their 'rawMatrixData' format (XMMATRIX).
	--- NOTE: The VIEW Matrix is initialized from within 'Camera'.
	*/
	void InitializeConstantMatrices();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creating and Setting the ConstantBuffer by:
	--- Defining the settings (D3D11_BUFFER_DESC).
	--- 'Packaging'/'Initiating' the data (D3D11_SUBRESOURCE_DATA).
	--- Creating the buffer via D3D-Device (Device->CreateBuffer()).
	--- Set the buffer (decide which shader should have access to the buffer).
	*/
	void CreateSetConstantBuffers();

public:
	ConstantBufferManager();
	~ConstantBufferManager();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes the Constant Buffer Manager by:
	--- Initializing the Constant Matrices.
	--- 'Packaging' said Constant Matrices into a '4x4' format.
	--- Create the Constant Buffer (D3D11_BUFFER_DESC & D3D11_SUBRESOURCE_DATA).
	*/
	void Initialize();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Re-formats the WORLD, VIEW, & PROJECTION matrix data.
	2. Format Change Details: XMMATRIX --> XMFLOAT4X4.
	*/
	void packageMatrices();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calls 'this->ConstantBuffer->Release()'.
	2. ConstantBuffer is of the 'ID3D11Buffer' type.
	*/
	void releaseAll();

	MatrixBufferPack	*GETpackagedMatrixData();
	ID3D11Buffer*		*GETconstantBuffer();
};

//______________________________________________//
//                                              //
//        END OF CONSTANT_BUFFER_MANAGER        //
//______________________________________________//
//////////////////////////////////////////////////

#endif