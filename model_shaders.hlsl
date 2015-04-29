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

	float diffuse_amount = dot(directional_light_vector, normal);
	diffuse_amount = saturate(diffuse_amount);


	// Determine the light positions based on the position of the lights and the position of the vertex in the world.
	float4 lightPos1 = lightPosition[0] - position;
		float4 lightPos2 = lightPosition[1] - position;
		float4 lightPos3 = lightPosition[2] - position;
		float4 lightPos4 = lightPosition[3] - position;

		// Normalize the light position vectors.
		lightPos1 = normalize(lightPos1);
	lightPos2 = normalize(lightPos2);
	lightPos3 = normalize(lightPos3);
	lightPos4 = normalize(lightPos4);

	float lightIntensity1 = saturate(dot(normal, lightPos1));
	float lightIntensity2 = saturate(dot(normal, lightPos2));
	float lightIntensity3 = saturate(dot(normal, lightPos3));
	float lightIntensity4 = saturate(dot(normal, lightPos4));

	// Determine the diffuse color amount of each of the four lights.
	float4 color1 = diffuseColor[0] * lightIntensity1;
		float4 color2 = diffuseColor[1] * lightIntensity2;
		float4 color3 = diffuseColor[2] * lightIntensity3;
		float4 color4 = diffuseColor[3] * lightIntensity4;

		float pColour = saturate(color1 + color2 + color3 + color4);

	if (pColour == 0)
		output.color = (ambient_light_colour + (directional_light_colour*diffuse_amount));
	else
		output.color = (ambient_light_colour + (directional_light_colour*diffuse_amount))*pColour;

	return output;
}
float4 ModelPS(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{

	return color  * texture0.Sample(sampler0, texcoord);
}

