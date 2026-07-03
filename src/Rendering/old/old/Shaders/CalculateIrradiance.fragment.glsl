#version 410

#include "SphericalCoordinates.glsl"

layout(location = 0) in vec2 texCoords;

uniform sampler2D environmentTexture;

layout(location = 0) out vec4 outColor;


void main()
{
	vec2 azimutElevation = texCoordsToSphericalCoords(texCoords);
	vec3 normal = sphericalCoordsToCartesianCoords(azimutElevation);
	normal = normalize(normal);

	vec3 up = vec3(0, 1, 0);
	vec3 right = normalize(cross(up, normal));
	up = normalize(cross(normal, right));

	vec2 stepSize = vec2(0.174533) ;// vec2(10 * DEGREES_TO_RADIANS);
	float numSamples = 0.0;
	vec3 irradiance = vec3(0);

	for (float azimut = 0.0; azimut < M_TWO_PI; azimut += stepSize.x)
	{
		for (float elevation = 0.0; elevation < M_HALF_PI; elevation += stepSize.y)
		{
			// spherical to cartesian (in tangent space)
			vec3 tangentSample = normalize(vec3(sin(elevation) * cos(azimut),  sin(elevation) * sin(azimut), cos(elevation)));
			// tangent space to world
			vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * normal; 
			vec2 sampleTexCoords = sphericalCoordsToTexCoords(cartesianCoordsToSpericalCoords(sampleVec));
			
			irradiance += texture(environmentTexture, sampleTexCoords).rgb * cos(elevation) * sin(elevation);
			numSamples++;
		}
	}
	
	irradiance *= M_PI / (numSamples);

	outColor = vec4(irradiance, 1.0);
}