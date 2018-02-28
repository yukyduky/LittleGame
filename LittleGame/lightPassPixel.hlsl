Texture2D texPosition	: register(t0);
Texture2D texNormal		: register(t1);
Texture2D texDiffuse	: register(t2);

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

static const int MAX_NUM_LIGHTS = 50;
static const int MAX_NUM_FLOORGRIDS_X = 35;
static const int MAX_NUM_FLOORGRIDS_Y = 35;

cbuffer GeneralData : register (b0) {
	FloorGrid grid[MAX_NUM_FLOORGRIDS_X][MAX_NUM_FLOORGRIDS_Y];
	float3 camPos;
	float nrOfLights;
	float3 camDir;
	float pad0;
	float2 arenaDims;
	float2 gridDims;
	float2 gridStartPos;
	float2 pad1;
}

cbuffer Light : register (b1) {
	PointLight Lights[MAX_NUM_LIGHTS];
}

void loadGeoPassData(in float2 screenCoords, out float3 pos_W, out float3 normal, out float3 diffuse, out float emission);
void renderFallingFloor(inout float3 pos_W, inout float3 normal, inout float3 diffuse);
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

	renderFallingFloor(pos_W, normal, diffuse);

	float4 finalColor = calcLight(pos_W, normal, diffuse, emission);

	return finalColor;
}

void loadGeoPassData(in float2 screenCoords, out float3 pos_W, out float3 normal, out float3 diffuse, out float emission)
{
	int3 texCoords = int3(screenCoords, 0.0f);

	pos_W = texPosition.Load(texCoords).xyz;
	normal = texNormal.Load(texCoords).xyz;
	diffuse = texDiffuse.Load(texCoords).xyz;
	emission = texDiffuse.Load(texCoords).w;
	normal = float3(0.0f, 1.0f, 0.0f);
}

void renderFallingFloor(inout float3 pos_W, inout float3 normal, inout float3 diffuse)
{
	if (pos_W.y == -0.5f) {
		float3 pToC = pos_W - camPos;
		normalize(pToC);
		float lDotN = dot(pToC, normal);
		if (lDotN != 0.0f) {
			float i = 0.0f;
			bool intersected = false;
			float3 p = float3(0.0f, 0.0f, 0.0f);
			int xGrid = 0;
			int yGrid = 0;

			do {
				float pOnQuadX = pos_W.x + pToC.x * (gridDims.x / 10.0f) * i; // gridDims.x / 2.0f stepsize
				float pOnQuadZ = pos_W.z + pToC.z * (gridDims.y / 10.0f) * i;

				xGrid = (pOnQuadX - gridStartPos.x) / gridDims.x;
				yGrid = (pOnQuadZ - gridStartPos.y) / gridDims.y;

				if (xGrid >= 0 && xGrid < MAX_NUM_FLOORGRIDS_X && 
					yGrid >= 0 && yGrid < MAX_NUM_FLOORGRIDS_Y) {
					float d = dot(float3(pOnQuadX, grid[xGrid][yGrid].height, pOnQuadZ) - camPos, normal) / lDotN;
					p = d * pToC + camPos;

					if (p.x >= pOnQuadX - 1.0f && p.x < pOnQuadX + gridDims.x + 0.0f &&
						p.z >= pOnQuadZ - 1.0f && p.z < pOnQuadZ + gridDims.y + 0.0f)
					{
						intersected = true;
						pos_W.y = p.y;
						diffuse = grid[xGrid][yGrid].color;
					}
				}
				else {
					break;
				}

				i += 1.0f;
			} while (!intersected);

			if (!intersected)
			{
				diffuse = float3(0.0f, 0.0f, 0.0f);
			}
		}
	}












	/*int xGrid = pos_W.x % gridDims.x < MAX_NUM_FLOORGRIDS_X ? pos_W.x % gridDims.x : MAX_NUM_FLOORGRIDS_X - 1;
	int yGrid = pos_W.z % gridDims.y < MAX_NUM_FLOORGRIDS_Y ? pos_W.z % gridDims.y : MAX_NUM_FLOORGRIDS_Y - 1;



	if (pos_W.y < (grid[xGrid][yGrid].height * scaleHeight) + gridStartPos.y) {
		diffuse = grid[xGrid][yGrid].color;
	}
	else if (pos_W.y < (grid[xGrid][yGrid].height * scaleDepth) + gridStartPos.y)

	if (objectType == 0.5f) {
		
	}
	else {
		float3 pToC = camPos - pos_W;

		int xGrid = pos_W.x % gridDims.x < MAX_NUM_FLOORGRIDS_X ? pos_W.x % gridDims.x : MAX_NUM_FLOORGRIDS_X - 1;
		int yGrid = pos_W.z % gridDims.y < MAX_NUM_FLOORGRIDS_Y ? pos_W.z % gridDims.y : MAX_NUM_FLOORGRIDS_Y - 1;

		while (xGrid != MAX_NUM_FLOORGRIDS_X - 1 && yGrid != MAX_NUM_FLOORGRIDS_Y) {
			
		}
	}*/
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

float dot(float3 vec1, float3 vec2)
{
	return float(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

void normalize(inout float3 vec)
{
	float mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec = float3(vec.x / mag, vec.y / mag, vec.z / mag);
}