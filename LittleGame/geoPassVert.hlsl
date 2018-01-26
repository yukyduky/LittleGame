struct VS_IN {
	float3 pos		: POSITION;
	float3 normal	: NORMAL;
	float4 color	: COLOR;
};

struct VS_OUT {
	float4 pos		: SV_POSITION;
	float3 normal	: NORMAL;
	float4 color	: COLOR;
};

VS_OUT VS(VS_IN input) {
	VS_OUT output;

	output.pos = float4(input.pos, 1.0f);
	output.normal = input.normal;
	output.color = input.color;

	return output;
}