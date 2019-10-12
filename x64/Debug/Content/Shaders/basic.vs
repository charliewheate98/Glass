#version 440 core 

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 m_ViewProjection;
uniform mat4 m_Transform;

out vec2 TexCoords;

void main()
{
	gl_Position = m_ViewProjection * m_Transform * vec4(position, 1.0f);
	TexCoords = vec2(texCoords.x, texCoords.y);
}