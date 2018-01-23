struct VS_IN {
	float3 position		: POSITION;
	float4 color		: COLOR;
};

struct VS_OUT {
	float4 position		: SV_POSITION;
	float4 color		: COLOR;
};

VS_OUT VS(VS_IN input)
{
	VS_OUT output;

	output.position = float4(input.position, 1.0);
	output.color = input.color;

	return output;
}