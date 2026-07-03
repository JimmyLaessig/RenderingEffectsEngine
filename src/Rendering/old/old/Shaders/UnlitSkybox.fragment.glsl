#version 410

#include "SphericalCoordinates.glsl"

layout(location = 0) in vec2 texCoords;

uniform sampler2D skyboxTexture;

uniform mat4 inverseViewProjectionMatrix;

layout(location = 0) out vec4 outBaseColor;
layout(location = 1) out vec4 outNormal;
layout(location = 2) out vec4 outOcclusionRoughnessMetallic;

void main()
{
	vec4 ndc = vec4(texCoords * 2.0 - 1.0, 1.0, 1.0);

	vec4 worldPos = inverseViewProjectionMatrix * ndc;
	worldPos /= worldPos.w;

	vec3 dir = normalize(worldPos.xyz);
	vec2 sphericalCoords = cartesianCoordsToSpericalCoords(dir);

	vec2 uvs = sphericalCoordsToTexCoords(sphericalCoords);
	outBaseColor	= texture(skyboxTexture, uvs);
	outBaseColor.a	= 0.f;

	outNormal.xyz	= -dir;
	outNormal.w		= 1.f;

	outOcclusionRoughnessMetallic = vec4(1.0, 0.0, 0.0, 0.0);
}

