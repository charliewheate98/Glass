#version 440 core 

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D m_Diffuse;

void main()
{
	FragColor = texture(m_Diffuse, TexCoords);
}