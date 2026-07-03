#version 420
#extension GL_KHR_vulkan_glsl: enable

#include "MaterialBase.fragment.glsl"


layout(set = PERMATERIAL_DESCRIPTORSET, binding = 0) uniform material
{
	vec4 baseColor;
};

layout(set = PERMATERIAL_DESCRIPTORSET, binding = 1) uniform sampler2D baseColorTexture;

void fragmentShader(in FragmentShaderInput shaderInput, inout FragmentShaderOutput shaderOutput)
{
	shaderOutput.baseColor = texture(baseColorTexture, shaderInput.texcoord0).rgb * baseColor.rgb;
}
