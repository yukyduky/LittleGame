//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//																					//
//							    	Input & Output									//
//																					//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct VertexInput {
	// According to DeferredShader's InputLayout
	float3 Position	: POSITION;
//	float2 TexUV	: TEXCOORD;
	float3 Normal	: NORMAL;
};

struct VertexOutput {
	// Same as VertexInput but float3->float4
	float4 Position	: SV_POSITION;
	//	float2 TexUV	: TEXCOORD;
	float4 Normal	: NORMAL;
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//																					//
//							    	Main Function									//
//																					//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

VertexOutput VertexMain(VertexInput input) {
	VertexOutput output = (VertexOutput)0;

	output.Position = float4(input.Position, 1);	// '1' because it's a point
//	output.TexUV = input.TexUV;
	output.Normal = float4(input.Position, 0);		// '0' because it's a vector

	return output;
}