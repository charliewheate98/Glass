// shader version
#version 440 core 

// location attributes
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

// uniform variables
uniform mat4 m_ViewProjection;
uniform mat4 m_Transform;

// outputs to the fragment shader
out vec2 TexCoords;

// main entry point for the shader
void main()
{
	gl_Position = m_ViewProjection * m_Transform * vec4(position, 1.0f);

	// Initialise Texture Coordinates
	TexCoords = vec2(texCoords.x, texCoords.y);
}