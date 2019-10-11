#version 440 core 

layout (location = 0) in vec3 position;

uniform mat4 m_ViewProjection;
uniform mat4 m_Transform;

void main()
{
	gl_Position = m_ViewProjection * m_Transform * vec4(position, 1.0f);
}