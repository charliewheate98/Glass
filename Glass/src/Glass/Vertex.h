#pragma once

#include <glm.hpp>

struct Vertex
{
	glm::vec3 _v;

	Vertex(glm::vec3 v)
	{
		_v = v;
	}

	~Vertex() {}
};