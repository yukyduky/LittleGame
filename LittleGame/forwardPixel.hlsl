struct PS_IN {
	float4 position		: SV_POSITION;
	float4 color		: COLOR;
};

float4 PS(PS_IN input) : SV_TARGET
{
	return float4(1.0, 0.0, 1.0, 1.0);
}