#ifndef COMMON_GLSL_
#define COMMON_GLSL_

#define M_PI 3.1415926535897932384626433832795f

// Calculate a tangent-base matrix
mat3 tbn(vec3 n, vec3 t)
{
	vec3 b = normalize(cross(n, t));

	return mat3(t, b, n);
}


// Calculate a bumped normal based on a normal map
vec3 bumpedNormal(vec3 normal, vec3 tangent, sampler2D normalTexture, vec2 texcoords)
{
	mat3 tbn = tbn(normal, tangent);

	vec3 normalTS = normalize(texture(normalTexture, texcoords).rgb * 2.f - 1.f);
	
	return normalize(tbn * normalTS);
}


// GGX/Trowbridge-Reitz normal distribution function
float D_GGX(float alpha, float NdotH)
{
	float alphaSquared = alpha * alpha;

	float f = NdotH * NdotH * (alphaSquared - 1.f) + 1.f;

	return alphaSquared / (M_PI * f * f);
}


/// Schlick-Beckmann function
float G1(float alpha, float NdotX)
{
 	float k = alpha * 0.5f;

	return NdotX / (NdotX * (1.f - k) + k);
}


float Schlick_GGX(float alpha, float NdotV, float NdotL)
{
	return G1(alpha, NdotV) * G1(alpha, NdotL);
}


vec3 Schlick_Frensel(float VdotH, vec3 f0)
{
	return f0 + (1.f - f0) * pow(1.f - abs(VdotH), 5.f);
}

/// Calculate the PBR lighting
/**
 * \note: V, L, N must be in the same space
 * \param V Normalized vector from shading location to the eye
 * \param L Normalized vector from the shading location to the light source
 * \param N Surface normal vector
 * \param baseColor The base color of the material
 * \param roughness The perceptual roughness of the material
 * \param metallic The metallicness of the material
 * \param lightIndensity The intensity of the light source
 */
vec3 PBR(vec3 V, vec3 L, vec3 N, vec3 baseColor, float roughness, float metallic, vec3 lightIntensity)
{
	vec3 diffuseColor = mix(baseColor.rgb, vec3(0.f), metallic);
	vec3 f0 = mix(vec3(0.04f), baseColor, metallic);

	float alpha = roughness * roughness;
	
	vec3 H = normalize(V + L);

	float NdotL = dot(N, L);
	float NdotV = dot(N, V);
	float NdotH = dot(N, H);
	float VdotH = dot(V, H);

	vec3 F = Schlick_Frensel(VdotH, f0);

	vec3 diffuseBRDF = (1.f - F) * diffuseColor / M_PI;

	vec3 specularBRDF = F * D_GGX(alpha, NdotH) * Schlick_GGX(alpha, NdotV, NdotL)  / (4.f * abs(NdotV) * abs(NdotL));

	return (diffuseBRDF + specularBRDF) * lightIntensity * NdotL;
}

#endif // !COMMON_GLSL