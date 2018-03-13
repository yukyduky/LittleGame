Texture2D texPosition	: register(t0);
Texture2D texNormal		: register(t1);
Texture2D texDiffuse	: register(t2);
Texture2D texBackground	: register(t3);

SamplerState gSampler	: register(s0);

struct PointLight
{
	float3 pos;
	float pad0;
	float3 diffuse;
	float pad1;
	float3 ambient;
	float pad2;
	float3 attenuation;
	float specPower;
};

struct FloorGrid
{
	float3 color;
	float height;
};

struct PulseGrid
{
	float2 coords;
	float2 pad0;
};

static const int MAX_NUM_LIGHTS = 150;
static const int MAX_NUM_FLOORGRIDS = 36;

cbuffer GeneralData : register (b0) {
	FloorGrid grid[MAX_NUM_FLOORGRIDS][MAX_NUM_FLOORGRIDS];
	PulseGrid gridPulse[2][MAX_NUM_FLOORGRIDS + 1];
	float3 camPos;
	float nrOfLights;
	float2 arenaDims;
	float2 gridDims;
	float2 gridStartPos;
	float2 screenDims;
	float deltaTime;
	float3 pad0;
}

cbuffer Light : register (b1) {
	PointLight Lights[MAX_NUM_LIGHTS];
}

void loadGeoPassData(in float2 screenCoords, out float3 pos_W, out float3 normal, out float3 diffuse, out float emission);
void renderFloor(inout float3 pos_W, inout float3 normal, inout float3 diffuse);
float4 sampleBackground(in float2 screenCoords);
float4 calcLight(in float3 pos, in float3 normal, in float3 diffuse, in float emission);
float dot(float3 vec1, float3 vec2);
void normalize(inout float3 vec);

float4 PS(float4 position_S : SV_POSITION) : SV_TARGET
{
	float3 pos_W, normal, diffuse;
    float emission;
	// position_S.xy is literally screen coords
	float2 screenCoords = position_S.xy;

	// Load all the data from the geo pass
	loadGeoPassData(screenCoords, pos_W, normal, diffuse, emission);

	renderFloor(pos_W, normal, diffuse);

	float4 finalColor;

	if (diffuse.x + diffuse.z == 2.0f)
	{
		finalColor = float4(sampleBackground(screenCoords).xyz, 1.0f);
	}
	else
	{
		finalColor = calcLight(pos_W, normal, diffuse, emission);
	}

	return finalColor;
}

void loadGeoPassData(in float2 screenCoords, out float3 pos_W, out float3 normal, out float3 diffuse, out float emission)
{
	int3 texCoords = int3(screenCoords, 0.0f);

	pos_W = texPosition.Load(texCoords).xyz;
	normal = texNormal.Load(texCoords).xyz;
	diffuse = texDiffuse.Load(texCoords).xyz;
	emission = texDiffuse.Load(texCoords).w;
}

void renderFloor(inout float3 pos_W, inout float3 normal, inout float3 diffuse)
{
	if (pos_W.y == -0.5f)
	{
		float3 pToC = pos_W - camPos;
		normalize(pToC);

		float lDotN = dot(pToC, normal);
		if (lDotN != 0.0f)
		{
			float i = 0.0f;
			bool intersected = false;

			do
			{
				float pOnQuadX = pos_W.x + pToC.x * (gridDims.x / 4.0f) * i; // gridDims.x / 2.0f stepsize
				float pOnQuadY = pos_W.y + pToC.y * (gridDims.x / 4.0f) * i;
				float pOnQuadZ = pos_W.z + pToC.z * (gridDims.y / 4.0f) * i;

				int xGrid = (pOnQuadX - gridStartPos.x) / gridDims.x;
				int yGrid = (pOnQuadZ - gridStartPos.y) / gridDims.y;

				if (xGrid >= 0 && xGrid < MAX_NUM_FLOORGRIDS &&
					yGrid >= 0 && yGrid < MAX_NUM_FLOORGRIDS)
				{
					float height = grid[xGrid][yGrid].height;
					float d = dot(float3(pOnQuadX, pOnQuadY, pOnQuadZ) - camPos, normal) / lDotN;
					float3 p = d * pToC + camPos;

					float offsetX = 7.0f;
					float offsetY = 7.0f;
					float offsetZ = 7.0f;

					if (p.x >= pOnQuadX - offsetX && p.x < pOnQuadX + gridDims.x + offsetX &&
						p.z >= pOnQuadZ - offsetZ && p.z < pOnQuadZ + gridDims.y + offsetZ &&
						p.y >= height - offsetY && p.y < height + offsetY)
					{
						intersected = true;
						pos_W.y = p.y;
						diffuse = grid[xGrid][yGrid].color;
						diffuse -= abs(p.y) * deltaTime;
						saturate(diffuse);
					}
				}
				else
				{
					break;
				}

				i += 1.0f;

			} while (!intersected);

			if (!intersected)
			{				
				diffuse = float3(1.0f, 0.0f, 1.0f);				
			}
			else
			{
				float valueX = pos_W.x % gridDims.x;
				float valueZ = pos_W.z % gridDims.y;

				if (pos_W.x < arenaDims.x && 
					pos_W.z < arenaDims.y &&
					pos_W.y > -0.6f)
				{
					int xGrid = floor(pos_W.x / gridDims.x);
					int yGrid = floor(pos_W.z / gridDims.y);

					if (valueX >= gridDims.x * 0.5f)
					{
						xGrid++;
					}
					if (valueZ >= gridDims.y * 0.5f)
					{
						yGrid++;
					}

					float pulseRadius = pow(15.0f, 2);
					float3 baseColorLines = float3(0.0f, 0.0f, 0.3f);
					float3 baseColorPulse = float3(0.1f, 0.0f, 0.2f);
					float lineWidth = 1.0f / 16.0f;

					float pulseInfluence = 0.20f;

					for (int i = 0; i < MAX_NUM_FLOORGRIDS + 1; i++)
					{
						float pulseDistV = (pow(pos_W.x - gridPulse[0][i].coords.x, 2) + pow(pos_W.z - gridPulse[0][i].coords.y, 2)) * 3.14f;
						float pulseDistH = (pow(pos_W.x - gridPulse[1][i].coords.x, 2) + pow(pos_W.z - gridPulse[1][i].coords.y, 2)) * 3.14f;

						pulseInfluence += pulseRadius / pulseDistV + pulseRadius / pulseDistH;
					}

					float colorHardnessX = abs(pos_W.x - (xGrid * gridDims.x)) / (gridDims.x * lineWidth);
					float colorHardnessY = abs(pos_W.z - (yGrid * gridDims.y)) / (gridDims.y * lineWidth);

					if (colorHardnessX != 0.0f)
					{
						diffuse += baseColorLines / colorHardnessX;
						diffuse += baseColorPulse * pulseInfluence;
						saturate(diffuse);
					}
					if (colorHardnessY != 0.0f)
					{
						diffuse += baseColorLines / colorHardnessY;
						diffuse += baseColorPulse * pulseInfluence;
						saturate(diffuse);
					}
				}
			}

		}

		
	}
}

float4 sampleBackground(in float2 screenCoords)
{
	float2 texCoords = float2(screenCoords.x / screenDims.x, screenCoords.y / screenDims.y);

	float3 diffuse = texBackground.Sample(gSampler, texCoords).rgb;

	return float4(diffuse, 1.0f);
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
		float3 finalColor = lightIntensity * diffuse * Lights[i].diffuse;
		// Create an ambient color from the diffuse color of the object
		float3 finalAmbient = diffuse * Lights[i].ambient;
		// Calculate the light falloff factor, aka attenuation
		finalColor /= Lights[i].attenuation[0] + Lights[i].attenuation[1] * distance + Lights[i].attenuation[2] * distance * distance;
		finalAmbient /= Lights[i].attenuation[0] + Lights[i].attenuation[1] * distance + Lights[i].attenuation[2] * distance * distance;

		// Add the ambient
		pointLighting += finalColor + finalAmbient;
	}

	return float4(saturate(pointLighting), 1.0f);
}

float dot(float3 vec1, float3 vec2)
{
	return float(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

void normalize(inout float3 vec)
{
	float mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec = float3(vec.x / mag, vec.y / mag, vec.z / mag);
}