#version 410


layout(location = 0) in vec2 texCoords;

uniform sampler2D inputTexture;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 color = texture(inputTexture, texCoords).rgb;
	// Tone mapping
	color = color / (color + 1.f);
	outColor = vec4(color, 1.f);	
}