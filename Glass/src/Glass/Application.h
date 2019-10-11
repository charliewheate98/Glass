#pragma once

#include "pch.h"
#include "Core.h"

#include <GLFW/glfw3.h>

namespace Glass
{
	class GLASS_API Application
	{
	protected:
		GLFWwindow* window;
	public:
		Application();
		virtual ~Application();

		inline GLFWwindow* GetWindow() { return window; }

		virtual void MainLoop();
		virtual void Tick(float DeltaTime);
		virtual void Render();
	};
}
