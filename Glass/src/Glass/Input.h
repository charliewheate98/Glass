#pragma once

#include "Application.h"

namespace Glass
{
	class Input 
	{
	public:
		static bool IsKeyPressed(int keycode)
		{
			auto window = &Application::GetWindow();
			auto state = glfwGetKey(window, keycode);
		
			return state;
		}
	};
}
