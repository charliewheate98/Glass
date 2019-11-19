#version 440 core 

out vec4 FragColor;

in PassData
{
	vec2 TexCoords;
} inData;

uniform vec3 m_Colour;

void main()
{
	FragColor = vec4(1.0, 0.5, 0.3, 1.0);		
}