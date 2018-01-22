//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//																					//
//							      Constant Buffers									//
//																					//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
cbuffer ConstantBufferA : register(b0) {

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//																					//
//							    	Input & Output									//
//																					//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

struct GeometryInput {
	// Same as VertexOutput
	float4 Position	: SV_POSITION;
	//float2 TexUV	: TEXCOORD;
	float4 Normal	: NORMAL;
};

struct GeometryOutput {
	// Same as GeometryInput but also with added ConstantBufferData
	float4 Position	: SV_POSITION;
//	float2 TexUV	: TEXCOORD;
	float4 Normal	: NORMAL;

//	worldPos	- needed for shadowmapping?
//	Kd			- needed for specular lighting.

};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//																					//
//							    	Main Function									//
//																					//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
[maxvertexcount(3)]	// ??
void GeometryMain(triangle GeometryInput triangle_input[3], inout TriangleStream<GeometryOutput> outputStream) {
	GeometryOutput output = (GeometryOutput)0;

	for (int i = 0; i < 3; i++) {




		outputStream.Append(output);
	}

	outputStream.RestartStrip();
}