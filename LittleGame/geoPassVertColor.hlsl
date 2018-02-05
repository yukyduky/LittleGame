struct VS_IN {
	float3 pos_M	: POSITION;
	float3 normal	: NORMAL;
	float4 color	: COLOR;
};

struct VS_OUT {
	float4 pos_S	: SV_POSITION;
	float4 pos_W	: POSITION;
	float4 normal	: NORMAL;
	float4 color	: COLOR;
};

cbuffer cbGeoColor : register(b0)
{
	float4x4 world;
	float4x4 wvp;
};

VS_OUT VS(VS_IN input) {
	VS_OUT output;

	// Convert the vertices pos from Model space to World space
	// Uncomment once the constant buffers work
	output.pos_S = mul(float4(input.pos_M, 1.0f), wvp);
	output.pos_W = mul(float4(input.pos_M, 1.0f), world);
	output.normal = normalize(mul(float4(input.normal, 1.0f), world));
	output.color = input.color;

	return output;
}