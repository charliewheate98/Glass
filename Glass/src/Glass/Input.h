#pragma once

#include "pch.h"
#include "Core.h"
#include <GLFW/glfw3.h>

namespace Glass
{
	class Input 
	{
	public:
		static bool IsKeyPressed(GLFWwindow& window, int keycode)
		{
			auto state = glfwGetKey(&window, keycode);
			return state;
		}
	};
}
