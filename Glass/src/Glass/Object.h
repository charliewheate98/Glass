#pragma once

#include "Core.h"

namespace Glass
{
	class GLASS_API Object
	{
	private:
	public:
		Object() {}
		virtual ~Object() {}

		virtual void Tick(float DeltaTime) {}
		virtual void Render() {}
	};
}


