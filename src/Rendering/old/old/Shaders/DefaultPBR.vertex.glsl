#version 420

#include "MaterialBase.vertex.glsl"

layout(std140, set = 0, binding = 1) uniform LightData
{
	vec3 color;
	vec3 direction;
} lightData;

layout(set = 0, binding = 2) uniform sampler2D colorTexture;

void vertexShader(in VertexShaderInput shaderInput, inout VertexShaderOutput shaderOutput)
{

}