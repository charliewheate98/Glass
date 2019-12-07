#version 440 core 

out vec4 FragColor;

in PassData
{
	vec2 TexCoords;
	float tid;
	vec3 pos;
} inData;

uniform sampler2D m_Diffuse[2];

void main()
{
	FragColor = vec4(1.0, 0.0, 0.0, 1.0);

}