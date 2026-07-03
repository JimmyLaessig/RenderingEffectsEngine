#version 410

layout(location = 0) in vec2 texCoords;

uniform sampler2D inputTexture;
uniform float oneOverGamma = 1.0 / 2.2;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 color = texture(inputTexture, texCoords).rgb;
	outColor.rgb = pow(color, vec3(oneOverGamma));
	outColor.a = 1.0f;
}
