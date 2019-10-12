#pragma once

#include "pch.h"
#include "Core.h"

#include <GLFW/glfw3.h>

namespace Glass
{
	class GLASS_API Application
	{
	protected:
		static GLFWwindow* window;
	public:
		Application();
		virtual ~Application();

		static GLFWwindow& GetWindow() { return *window; }

		virtual void MainLoop();
		virtual void Tick();
		virtual void Render();
	};
}
