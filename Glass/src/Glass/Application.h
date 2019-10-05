#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API Application
	{
	private:
	public:
		Application();
		virtual ~Application();

		virtual void MainLoop();
		virtual void Tick(float DeltaTime);
		virtual void Render();
	};
}



