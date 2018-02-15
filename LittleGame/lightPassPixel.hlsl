Texture2D texPosition	: register(t0);
Texture2D texNormal		: register(t1);
Texture2D texDiffuse	: register(t2);

struct PointLight {
	float3 pos;
	float pad0;
	float3 diffuse;
	float pad1;
	float3 ambient;
	float pad2;
	float3 attenuation;
	float specPower;
};

static const int MAX_NUM_LIGHTS = 3;

cbuffer GeneralData : register (b0) {
	float nrOfLights;
	float3 pad0;
}

cbuffer Light : register (b1) {
	PointLight Lights[MAX_NUM_LIGHTS];
}

void loadGeoPassData(in float2 screenCoords, out float3 pos_W, out float3 normal, out float3 diffuse, out float emission);
float4 calcLight(in float3 pos, in float3 normal, in float3 diffuse, in float emission);

float4 PS(float4 position_S : SV_POSITION) : SV_TARGET
{
	float3 pos_W, normal, diffuse;
	float emission;
	// position_S.xy is literally screen coords
	float2 screenCoords = position_S.xy;

	// Load all the data from the geo pass
	loadGeoPassData(screenCoords, pos_W, normal, diffuse, emission);

	float4 finalColor = calcLight(pos_W, normal, diffuse, emission);

	return finalColor;
	//return float4(0.0f, 1.0f, 1.0f, 1.0f);
}

void loadGeoPassData(in float2 screenCoords, out float3 pos_W, out float3 normal, out float3 diffuse, out float emission)
{
	int3 texCoords = int3(screenCoords, 0.0f);

	pos_W = texPosition.Load(texCoords).xyz;
	normal = texNormal.Load(texCoords).xyz;
	diffuse = texDiffuse.Load(texCoords).xyz;
	emission = texDiffuse.Load(texCoords).w;
}

float4 calcLight(in float3 pos, in float3 normal, in float3 diffuse, in float emission)
{
	//float3 pointLighting = float3(0.0f, 0.0f, 0.0f);
	float3 pointLighting = diffuse * emission;

	for (int i = 0; i < nrOfLights; i++) {
		// Vector from object to light
		float3 pToL = Lights[i].pos - pos;
		// Length of the vector is the distance between the object to the light
		float distance = length(pToL);
		// Normalize pToL
		pToL /= distance;

		// Calculate the "angle" between the normal and the light vector
		float lightIntensity = saturate(dot(normal, pToL));
		// Calculate the diffuse against the light and multiply with the light diffuse color
		float3 finalColor = lightIntensity * diffuse * Lights[i].diffuse.xyz;
		// Calculate the light falloff factor, aka attenuation
		finalColor /= Lights[i].attenuation[0] + Lights[i].attenuation[1] * distance + Lights[i].attenuation[2] * distance * distance;

		// Create an ambient color from the diffuse color of the object
		float3 finalAmbient = diffuse * Lights[i].ambient;

		// Add the ambient
		pointLighting += finalColor + finalAmbient;
	}

	return float4(saturate(pointLighting), 1.0f);
}
