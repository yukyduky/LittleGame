#pragma
#ifndef ICONSTANTBUFFERMANAGER_H
#define ICONSTANTBUFFERMANAGER_H

#include "D3D.h"
#include <d3d11.h>
#include <DirectXMath.h>





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
|                                         |
|       I_CONSTANT_BUFFER_MANAGER         |
-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/

class IConstantBufferManager {
public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes the Constant Buffer Manager by:
	--- Initializing the Constant Matrices.
	--- 'Packaging' said Constant Matrices into a '4x4' format.
	--- Create the Constant Buffer (D3D11_BUFFER_DESC & D3D11_SUBRESOURCE_DATA).
	*/
	virtual void initialize() = 0;
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Re-formats the WORLD, VIEW, & PROJECTION matrix data.
	2. Format Change Details: XMMATRIX --> XMFLOAT4X4.
	*/
	virtual void packageMatrices() = 0;
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. NON-CLASS FUNCTION.
	2. Allows us to edit the data within the Constant Buffers.
	--- DeviceContext()->Map() 'opens' the ID3D11Buffer for writing.
	--- 'memcpy' copies the data from our already packaged MatrixBufferPack.
	--- DeviceContext()->Unmap() 'closes' the ID3D11Buffer.
	*/
	virtual void editConstantBuffers(ID3D11Buffer** targetBuffer, void* targetStruct, size_t targetStructSize) = 0;
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calls 'this->ConstantBuffer->Release()'.
	2. ConstantBuffer is of the 'ID3D11Buffer' type.
	*/
	virtual void releaseAll() = 0;
};

//______________________________________________//
//                                              //
//        END OF ICONSTANT_BUFFER_MANAGER        //
//______________________________________________//
//////////////////////////////////////////////////

#endif