/**
AGP Assignment
model_shaders.hlsl
Purpose: shader for the models

@author Sarah Bulk
*/

/////////////
// DEFINES //
/////////////
#define NUM_LIGHTS 4

cbuffer CB0
{
	matrix WVPMatrix;
	float4 directional_light_vector;
	float4 directional_light_colour;
	float4 ambient_light_colour;

	float4 lightPosition[NUM_LIGHTS];
	float4 diffuseColor[NUM_LIGHTS];
	float  range[NUM_LIGHTS];
};

Texture2D texture0;
SamplerState sampler0;

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};


VOut ModelVS(float4 position : SV_POSITION, float2 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;

	output.position = mul(WVPMatrix, position);

	output.texcoord = texcoord;

	//Light contribution

	//directional and ambient light
	float diffuse_amount = dot(directional_light_vector, normal);
	diffuse_amount = saturate(diffuse_amount);

	//Point lights
	float pColour;

	for (uint i = 0; i < NUM_LIGHTS; i++)
	{

		// Determine the diffuse color amount of the current point light
		float distt = distance(lightPosition[i], position);
		float lightIntensity = 1 - saturate(distt / range[i]);
		lightIntensity = pow(lightIntensity, 2);
		float4 currColor = diffuseColor[i] * lightIntensity;

		//add the point light colour
		pColour += currColor;

	}

	pColour = saturate(pColour);

	output.color = (ambient_light_colour + (directional_light_colour*diffuse_amount)) + pColour;

	return output;
}
float4 ModelPS(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{

	return color  * texture0.Sample(sampler0, texcoord);
}

