#version 410

#include "SphericalCoordinates.glsl"

layout(location = 0) in vec2 texCoords;

uniform sampler2D depthTexture;
uniform sampler2D baseColorTexture;
uniform sampler2D normalTexture;
uniform sampler2D materialTexture;

uniform sampler2D occlusionTexture;
uniform sampler2D irradianceTexture;


uniform mat4 inverseViewProjectionMatrix;
uniform vec3 cameraPosition;

uniform vec3 lightColor;

layout(location = 0) out vec4 outColor;

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main()
{
	vec3 baseColor	= texture(baseColorTexture, texCoords).rgb;
	vec4 material	= texture(materialTexture, texCoords);
	float occlusion = material.r;
	float metallic	= material.g;
	float roughness = material.b;
	float litMask	= material.a;

	float depth = texture(depthTexture, texCoords).r;
	vec4 position = inverseViewProjectionMatrix * vec4(texCoords, depth, 1.0);
	position /= position.w;

	float ambientOcclusion = min(texture(occlusionTexture, texCoords).r, occlusion);

	vec3 N					= normalize(texture(normalTexture, texCoords).rgb);
	vec2 sphericalCoords	= cartesianCoordsToSpericalCoords(N);
	vec2 uvs				= sphericalCoordsToTexCoords(sphericalCoords);
	vec3 irradiance			= texture(irradianceTexture, uvs).rgb;

	vec3 F0 = mix(vec3(0.04), baseColor, metallic);

	// vec3 V		= normalize(cameraPosition - position.xyz);
	// float NdotV	= dot(N, V);
	// vec3 kS = fresnelSchlick(max(NdotV, 0.0), F0);//, roughness);
	// vec3 kD = 1.0 - kS;
	// kD *= 1.0 - metallic;

	vec3 kD = (vec3(1.0) - vec3(metallic)) * (vec3(1.0) - F0);

	vec3 color = baseColor;//baseColor * lightColor * irradiance * kD * vec3(ambientOcclusion);

	color = mix(baseColor, color, litMask);
	outColor = vec4(color, 1.0);
}