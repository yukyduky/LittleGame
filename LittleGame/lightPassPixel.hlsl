Texture2D texPosition	: register(t0);
Texture2D texNormal		: register(t1);
Texture2D texDiffuse	: register(t2);

SamplerState gSampler	: register(s0);

float4 PS(float4 position : SV_POSITION) : SV_TARGET
{
	float3 texCoords = float3(position.xy, 0.0f);
	float4 color = float4(texDiffuse.Load(texCoords).xyz, 1.0f);
	return color;
}