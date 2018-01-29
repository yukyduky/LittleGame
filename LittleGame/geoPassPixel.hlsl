struct PS_IN
{
	float4 pos_W		: SV_POSITION;
	float3 normal		: NORMAL;
	float4 color		: COLOR;
};

struct PS_OUT
{
	float4 pos_W			: SV_TARGET0;
	float4 normal			: SV_TARGET1;
	float4 diffuse			: SV_TARGET2;
};

PS_OUT PS(PS_IN input)
{
	PS_OUT output;

	// Sample the texture for the diffuse light
	float4 diffuse = input.color;

	output.pos_W = input.pos_W;
	output.normal = float4(input.normal, 1.0f);
	output.diffuse = input.color;

	return output;
}