#pragma once

#include <glm.hpp>

struct Vertex
{
	glm::vec3 _v;
	glm::vec2 _uv;

	Vertex() = default;
	Vertex(glm::vec3 v, glm::vec2 uv)
	{
		_v = v;
		_uv = uv;
	}

	~Vertex() {}
};
