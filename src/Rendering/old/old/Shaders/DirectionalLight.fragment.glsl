#version 410

layout(location = 0) in vec2 texcoords;

uniform sampler2D normalTexture;
uniform sampler2D baseColorTexture;
uniform sampler2D materialTexture;
uniform sampler2D depthTexture;
uniform sampler2D shadowMapTexture;
uniform sampler3D shadowMapOffsetTexture;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform mat4 lightSpaceMatrix;
uniform mat4 inverseViewProjectionMatrix;

layout(location = 0) out vec4 outColor;


vec3 worldPosition()
{
	float depth = texture(depthTexture, texcoords).r;
	vec3 ndc	= vec3(texcoords, depth) * 2.0 - 1.0;

	vec4 worldPos = inverseViewProjectionMatrix * vec4(ndc, 1.0);

	return worldPos.xyz /  worldPos.w;
}


//float calculateShadowFactor()
//{
//	vec3 worldSpacePosition = worldPosition();
//
//	vec4 lightSpacePosition = lightSpaceMatrix * vec4(worldSpacePosition, 1.0);
//	lightSpacePosition /= lightSpacePosition.w;
//	lightSpacePosition = lightSpacePosition * 0.5 + 0.5;
//
//	float shadowDepth = texture(shadowMapTexture, lightSpacePosition.xy).r;
//
//	return shadowDepth > lightSpacePosition.z ? 1.0 : 0.0;
//}


//float calculateShadowFactorRandom(float nDotL)
//{
//	float bias = mix(0.001, 0.0, nDotL);
//
//	vec3 worldSpacePosition = worldPosition();
//	vec4 lightSpacePosition = lightSpaceMatrix * vec4(worldSpacePosition, 1.0);
//	lightSpacePosition /= lightSpacePosition.w;
//	lightSpacePosition = lightSpacePosition * 0.5 + 0.5;
//
//	float radius = 2.f;
//
//	ivec2 offsetCoords = ivec2(mod(gl_FragCoord.xy, textureSize(shadowMapOffsetTexture, 0).yz));
//
//	int filterSizeSquared = textureSize(shadowMapOffsetTexture, 0).x;
//	int filterSize = int(sqrt(filterSizeSquared));
//	
//	vec2 texelSize = 1.0 / textureSize(shadowMapTexture, 0).xy;
//
//	float sum = 0.0;
//	// We check the outermost elements in the filter first to do a potential
//	// early-out if all samples agree.
//	// The filter is setup so that the z-component of the offset texture contains
//	// a single random filter. The first elements contain the outermost elements.
//	for (int i = 0; i < filterSize; ++i)
//	{
//		vec2 offset = texelFetch(shadowMapOffsetTexture, ivec3(i, offsetCoords), 0).rg * radius;
//		float depth = texture(shadowMapTexture, lightSpacePosition.xy + offset * texelSize).r;
//		if (depth > lightSpacePosition.z)
//		{
//			sum++;
//		}
//	}
//
//	if (sum == 0 || sum == filterSize)
//	{
//		return sum / filterSize;
//	}
//
//	for (int i = 0; i < filterSizeSquared; ++i)
//	{
//		vec2 offset = texelFetch(shadowMapOffsetTexture, ivec3(i, offsetCoords), 0).rg * radius;
//		float depth = texture(shadowMapTexture, lightSpacePosition.xy + offset * texelSize).r;
//		if ((depth) > (lightSpacePosition.z - bias))
//		{
//			sum++;
//		}
//	}
//	
//	return sum / filterSizeSquared;
//}


void main()
{
	vec3 worldNormal = normalize(texture(normalTexture, texcoords).xyz);
	
	vec4 baseColor = texture(baseColorTexture, texcoords);

	vec4 material = texture(materialTexture, texcoords);

	float litMask = material.a;

	float NdotL = dot(worldNormal, normalize(lightDirection));

	float shadowFactor = 1.0f;//calculateShadowFactorRandom(abs(NdotL));

	outColor.rgb = baseColor.rgb * NdotL * litMask * shadowFactor;
	outColor.a = 1.f;
}