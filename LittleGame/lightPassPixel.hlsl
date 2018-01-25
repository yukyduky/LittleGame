/*Texture2D texPosition	: register(t0);
Texture2D texNormal		: register(t1);
Texture2D texDiffuse	: register(t2);

SamplerState gSampler	: register(s0);*/

float4 PS(float4 position : SV_POSITION) : SV_TARGET
{
	//float4 color = texDiffuse.Sample(gSampler, position.xy);


	return float4(1.0, 0, 0, 1.0);
}