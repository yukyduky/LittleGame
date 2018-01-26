Texture2D texPosition	: register(t0);
Texture2D texNormal		: register(t1);
Texture2D texColor	: register(t2);

cbuffer cbLightColor
{
	float4x4 wvp;
};

void LoadGeoPassData(in float2 quadCoords, out float3 pos_W, out float3 normal, out float3 color);

float4 PS(float4 position_S : SV_POSITION) : SV_TARGET
{
	float3 pos_W, normal, color;
	float2 quadCoords = position_S.xy;

	LoadGeoPassData(quadCoords, pos_W, normal, color);

	return float4(color, 1.0f);
}

void LoadGeoPassData(in float2 quadCoords, out float3 pos_W, out float3 normal, out float3 color)
{
	int3 texCoords = int3(quadCoords, 0.0f);

	pos_W = texPosition.Load(texCoords).xyz;
	normal = texNormal.Load(texCoords).xyz;
	color = texColor.Load(texCoords).xyz;
}