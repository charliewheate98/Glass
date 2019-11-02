#version 440 core 

out vec4 FragColor;

uniform sampler2D m_Diffuse;

// Geometry Shader
in PassData
{
	vec2 TexCoords;
} inData;

void main()
{
	//FragColor = texture(m_Diffuse, inData.TexCoords);	
	FragColor = vec4(1.0, 0.5, 0.3, 1.0);
}