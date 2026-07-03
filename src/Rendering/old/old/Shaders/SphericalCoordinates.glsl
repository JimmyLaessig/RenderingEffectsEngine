#ifndef SPHERICAL_GLSL_
#define SPHERICAL_GLSL_

#define M_PI 3.1415926535897932384626433832795
#define M_TWO_PI (M_PI * 2.0)
#define M_HALF_PI (M_PI * 0.5)

#define DEGREES_TO_RADIANS (M_PI / 180.0)

#define RADIANS_TO_DEGREES (180.0 / M_PI)

// Transform the cartesian coordinates to sperical coordinates
vec2 cartesianCoordsToSpericalCoords(vec3 v)
{
	return vec2(atan(v.z, v.x),  asin(v.y));
}


// Transform the sperical coordinates to cartesian coordinates
vec3 sphericalCoordsToCartesianCoords(vec2 azimutElevation)
{
	return vec3(cos(azimutElevation.y) * cos(azimutElevation.x),
				sin(azimutElevation.y),
				cos(azimutElevation.y) * sin(azimutElevation.x));
}


// Transform the sperical coordinates to texture coordinates
vec2 sphericalCoordsToTexCoords(vec2 azimutElevation)
{
	const vec2 invAtan = vec2(0.1591, 0.3183);
	return azimutElevation * invAtan + 0.5f;
}


// Transform the texture coordinates to texture sperical
vec2 texCoordsToSphericalCoords(vec2 texCoords)
{
	const vec2 invAtan = vec2(0.1591, 0.3183);

	return (texCoords - 0.5f) / invAtan;
}


#endif // !SPHERICAL_GLSL_