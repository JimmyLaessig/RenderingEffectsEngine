#version 410

layout(location = 0) in vec3 position;
layout(location = 0) out vec2 texcoords;

void main()
{
	texcoords = position.xy * 0.5f + 0.5f;
	gl_Position	= vec4(position, 1.0);
}