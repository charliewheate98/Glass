#pragma once

#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "Camera.h"
#include "Shader.h"

namespace Glass
{
	class GLASS_API Renderer
	{
	private:
		std::unique_ptr<Camera> camera;
	public:
		Renderer() = default;
		~Renderer() {}

		void Begin();
		void Submit(Object* obj, Shader* shader);
		void Clear();
	};
}



