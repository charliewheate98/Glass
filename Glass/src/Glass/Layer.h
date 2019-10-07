#pragma once

#include "pch.h"
#include "Core.h"
#include "Glass.h"

namespace Glass
{
	class GLASS_API Layer
	{
	protected:
		std::string name;
		uint32_t ZIndex;
	private:
		std::unique_ptr<Renderer> LayerRenderer;
		std::unique_ptr<Camera>   OrthoCamera;
	public:
		Layer();
		virtual ~Layer() {}

		virtual void Update(float DeltaTime) {}
		virtual void Render() {}

		void SetName(const std::string& layer_name) { name = layer_name; }

		uint32_t& GetZIndex() { return ZIndex; }
	};
}



