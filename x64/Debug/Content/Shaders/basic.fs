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
	float intensity = 1.0f / length(inData.pos - vec3(1.0f, 0.4f, 0.f));

	int tid = int(inData.tid + 0.5);
	FragColor = texture(m_Diffuse[tid], inData.TexCoords) * intensity;		
}