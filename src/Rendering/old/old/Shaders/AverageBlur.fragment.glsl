#version 410

layout(location = 0) in vec2 texCoords;

uniform int blurSize = 4;
uniform sampler2D sourceTexture;

layout(location = 0) out vec4 outColor;

void main()
{
	vec2 texelSize = 1.0 / vec2(textureSize(sourceTexture, 0));

	vec4 result = vec4(0);
	vec2 hlim = vec2(float(-blurSize) * 0.5 + 0.5);

	for (int i = 0; i < blurSize ;++i)
	{
		for (int j = 0; j < blurSize; ++j)
		{
			vec2 offset = (hlim + vec2(i, j)) * texelSize;
			result += texture(sourceTexture, texCoords + offset);
		}
	}

	outColor = result / (blurSize * blurSize);
}
