#version 410

#include "PBRTemplate.fragment.glsl"

#include "Common.glsl"

uniform sampler2D baseColorTexture;
uniform sampler2D normalTexture;
uniform sampler2D occlusionTexture;
uniform sampler2D roughnessTexture;
uniform sampler2D metallicTexture;

uniform int occlusionChannel;
uniform int roughnessChannel;
uniform int metallicChannel;

uniform vec3 baseColorFactor;

void fragmentShader(in FragmentShaderInput input, inout FragmentShaderOutput output)
{
	output.baseColor	= texture(baseColorTexture, input.texcoords).rgb * baseColorFactor;
	output.worldNormal	= bumpedNormal(input.worldNormal, input.worldTangent, normalTexture, input.texcoords);
	output.occlusion	= texture(occlusionTexture, input.texcoords)[occlusionChannel];
	output.roughness	= texture(roughnessTexture, input.texcoords)[roughnessChannel];
	output.metallic		= texture(metallicTexture, input.texcoords)[metallicChannel];
}