#include "Layer.h"

namespace Glass
{
	std::vector<std::shared_ptr<Layer>> LayerManager::m_Layers;

	Layer::Layer(std::string name, uint32_t index) :
		m_ZIndex(index),
		m_Name(name)
	{}
}

