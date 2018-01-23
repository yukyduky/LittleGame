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
void editConstantBuffers(
	ID3D11Buffer*			targetBuffer,
	MatrixBufferPack		targetStruct,
	ID3D11DeviceContext*	*DeviceContext
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

	void InitializeConstantMatrices();
	void CreateSetConstantBuffers(
		ID3D11Device*			*Device,
		ID3D11DeviceContext*	*DeviceContext
	);

public:
	ConstantBufferManager();
	~ConstantBufferManager();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initializes 
	*/
	void Initialize(
		ID3D11Device*			*Device,
		ID3D11DeviceContext*	*DeviceContext
	);
	void packageMatrices();
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