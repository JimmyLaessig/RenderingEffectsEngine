#version 410
#include "Common.glsl"

layout(location = 0) in vec2 texCoords;

uniform sampler2D inputTexture;

layout(location = 0) out vec4 outColor;

const float SUBPIXEL_SHIFT = 0.25f;

const float REDUCE_MIN = 1.0 / 128.0;
const float REDUCE_MUL = 1.0 / 8.0;
const float SPAN_MAX = 8.0;

// Implementation of FXAA algorithm
// https://www.geeks3d.com/20110405/fxaa-fast-approximate-anti-aliasing-demo-glsl-opengl-test-radeon-geforce/
void main()
{
	vec2 texelSize = 1.0 / textureSize(inputTexture, 0).xy;

	vec3 rgbM = texture(inputTexture, texCoords).rgb;

    vec3 luma = vec3(0.299, 0.587, 0.114);

	float lumaM = dot(luma, texture(inputTexture, texCoords).rgb);
	float lumaTL = dot(luma, texture(inputTexture, texCoords + vec2(-1, -1) * texelSize).rgb);
	float lumaTR = dot(luma, texture(inputTexture, texCoords + vec2( 1, -1) * texelSize).rgb);
	float lumaBL = dot(luma, texture(inputTexture, texCoords + vec2(-1,  1) * texelSize).rgb);
	float lumaBR = dot(luma, texture(inputTexture, texCoords + vec2( 1,  1) * texelSize).rgb);
	
	float lumaMin = min(lumaM, min(lumaTL, min(lumaTR, min(lumaBL, lumaBR))));
	float lumaMax = max(lumaM, max(lumaTL, max(lumaTR, max(lumaBL, lumaBR))));
	float avgLuma = (lumaTL + lumaTR + lumaBL + lumaBR + lumaM) * 0.2f;

	vec2 dir;
	dir.x = -((lumaTL + lumaTR) - (lumaBL + lumaBR));
	dir.y = (lumaTL + lumaBL) - (lumaTR + lumaBL);

	float dirReduce = max(avgLuma * REDUCE_MUL, REDUCE_MIN);
	float scale = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);

	dir *= scale;
	dir = clamp(dir, vec2(-SPAN_MAX, -SPAN_MAX), vec2(SPAN_MAX, SPAN_MAX)) * texelSize;

	vec3 result1 = 0.5f * (texture(inputTexture, texCoords + dir * vec2(1.0 / 3.0 - 0.5)).rgb +
						   texture(inputTexture, texCoords + dir * vec2(2.0 / 3.0 - 0.5)).rgb);

	vec3 result2 = 0.5f * (texture(inputTexture, texCoords + dir * vec2(0.0 / 3.0 - 0.5)).rgb +
						   texture(inputTexture, texCoords + dir * vec2(3.0 / 3.0 - 0.5)).rgb);
	
	result2 = (result1 + result2) * 0.5;

	float lumaResult2 = dot(result2, luma);

	if (lumaResult2 < lumaMin || lumaResult2 > lumaMax)
	{
		outColor = vec4(result1, 1.0);
	}
	else
	{
		outColor = vec4(result2, 1.0);
	}

	outColor = texture(inputTexture, texCoords);
	
//
//    vec2 dir; 
//    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
//    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
//
//	float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * REDUCE_MUL), REDUCE_MIN);
//    float rcpDirMin = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);
//    dir = min(vec2( SPAN_MAX,  SPAN_MAX), max(vec2(-SPAN_MAX, -SPAN_MAX), dir * rcpDirMin)) * texelSize.xy;
//
//    vec3 rgbA = (1.0/2.0) * (
//        texture(inputTexture, texCoords.xy + dir * (1.0/3.0 - 0.5)).xyz +
//        texture(inputTexture, texCoords.xy + dir * (2.0/3.0 - 0.5)).xyz);
//
//    vec3 rgbB = rgbA * (1.0/2.0) + (1.0/4.0) * (
//        FxaaTexLod0(tex, posPos.xy + dir * (0.0/3.0 - 0.5)).xyz +
//        FxaaTexLod0(tex, posPos.xy + dir * (3.0/3.0 - 0.5)).xyz);
//    float lumaB = dot(rgbB, luma);
//    if((lumaB < lumaMin) || (lumaB > lumaMax)) return rgbA;
//    return rgbB; }

}