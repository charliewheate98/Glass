// shader version
#version 440 core 

// location attributes
layout (location = 0) in vec3  position;
layout (location = 1) in vec2  texCoords;
layout (location = 2) in float tId;

// uniform variables
uniform mat4 m_ViewProjection;
uniform mat4 m_Transform;

// Texture Uniforms
//uniform float m_NumberOfRows; // number of rows in the texture
//uniform vec2 m_Offset; // texture offset 

// outputs to the fragment shader
out PassData
{
	vec2 TexCoords;
	float tid;
	vec3 pos;
} outData;

// main entry point for the shader
void main()
{
	gl_Position = m_ViewProjection * m_Transform * vec4(position, 1.0f);

	outData.TexCoords = texCoords;
	outData.tid = tId;
	outData.pos = position;
	
	//outData.TexCoords = (texCoords / m_NumberOfRows) + m_Offset;
}