#version 440 core 

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D fboTexture;

void main()
{
	FragColor = texture(fboTexture, TexCoords);
}