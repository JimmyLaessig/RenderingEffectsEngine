#version 410
#include "Common.glsl"

layout(location = 0) in vec2 texCoords;

uniform sampler2D selectionTexture;
uniform sampler2D selectionDepthTexture;

uniform vec4 selectionColor;

layout(location = 0) out vec4 outColor;


void main()
{
	vec2 texelSize = 1.0 / textureSize(selectionTexture, 0);

	float c = texture(selectionTexture, texCoords).r;
	float d = texture(selectionDepthTexture, texCoords).r;


	int count = 0;
	for (float x = -3; x <= 3; ++x)
	{
		for (float y = -3; y <= 3; ++y)
		{
			if (texture(selectionTexture, texCoords + vec2(x, y) * texelSize).r == c)
			{
				count++;
			}
		}
	}

	if (count >= 7 * 7 )
	{
		discard;
	}
	else
	{
		gl_FragDepth = d * 0.1;
		outColor = selectionColor;
	}
}