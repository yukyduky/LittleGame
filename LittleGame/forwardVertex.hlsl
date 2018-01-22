struct VS_IN {
	float3 position		: POSITION;
};

struct VS_OUT {
	float4 position		: SV_POSITION;
};

VS_OUT VS(VS_IN input)
{
	VS_OUT output;

	output.position = float4(input.position, 1.0);

	return output;
}