#version 410
#include "Common.glsl"

layout(location = 0) in vec2 texCoords;

const int numSamples = 16;

uniform sampler2D depthTexture;
uniform sampler2D normalTexture;
uniform sampler2D materialTexture;

uniform sampler2D noiseTexture;

uniform vec3[numSamples] samples;
uniform mat4 projectionMatrix;
uniform mat4 inverseProjectionMatrix;
uniform mat4 viewMatrix;

uniform float intensity = 1.0;
uniform float radius = 0.1;
uniform float power = 1.0;

layout(location = 0) out vec4 outColor;


/// Perform m * vec4(v, 1.0) followed by perspective division
vec3 mul(mat4 m, vec3 v)
{
	vec4 res = m * vec4(v, 1.0);
	return res.xyz / res.w;
}


vec3 viewSpaceNormal(vec2 uv)
{
	vec3 normal	= texture(normalTexture, uv).xyz;
	return normalize(mat3(viewMatrix) * normal);
}


vec3 viewSpacePosition(vec2 uv)
{
	float depth	= texture(depthTexture, uv).r;
	return mul(inverseProjectionMatrix, vec3(uv, depth) * 2.0 - 1.0);
}


// Implementation of Screen-space Ambient Occlusion algorithm
// http://john-chapman-graphics.blogspot.com/2013/01/ssao-tutorial.html
void main()
{
	vec2 noiseScale = vec2(textureSize(depthTexture, 0)) / vec2(textureSize(noiseTexture, 0));

	// Obtain the fragments normal and position in view space
	vec3 normalVS	= viewSpaceNormal(texCoords);
	vec3 positionVS	= viewSpacePosition(texCoords);

	// Create a tangent space around the normal with a randomized tangent
	vec3 randomVector	= texture(noiseTexture, texCoords * noiseScale).xyz;
	// Use the Graham-Schmidt process to compute an orthogonal basis
	vec3 tangent		= normalize(randomVector - normalVS * dot(randomVector, normalVS));
	vec3 bitangent		= normalize(cross (normalVS, tangent));
	mat3 tbn			= mat3(tangent, bitangent, normalVS);

	float occlusion = 0.0;
	 
	for (int i = 0; i < numSamples; ++i)
	{
		// Transform the sample position from tangent space to view space
		vec3 samplePosVS = positionVS + tbn * samples[i] * radius;
		
		// Project the sample position to clip space
		vec3 samplePosCS = mul(projectionMatrix, samplePosVS);

		// Get the position of the pixel under/over the projected sample point
		vec3 occluderVS = viewSpacePosition(samplePosCS.xy * 0.5 + 0.5);

		float sampleLinearDepth = -samplePosVS.z;
		float occluderLinearDepth = -occluderVS.z;

		// Only consider the sample if it lies within the radius

		float rangeCheck = smoothstep(0.0, 1.0, radius / abs(sampleLinearDepth - occluderLinearDepth));
		occlusion += (occluderLinearDepth <= sampleLinearDepth ? 1.0 : 0.0) * rangeCheck;
	}
	
	vec4 materialProperties = texture(materialTexture, texCoords);
	float litMask = materialProperties.a;

	occlusion = (occlusion / numSamples) * litMask * intensity;

	occlusion = 1.0 - occlusion;

	occlusion = pow(occlusion, power);
	outColor = vec4(occlusion, occlusion, occlusion, 1.0f);
	
}