#include "Renderer.h"

namespace Glass
{
	void Renderer::Begin()
	{
		// camera = std::make_unique<Camera>(param's);
	}

	void Renderer::Submit(Object* obj, Shader* shader)
	{
		shader->Bind();

		obj->Render();
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}