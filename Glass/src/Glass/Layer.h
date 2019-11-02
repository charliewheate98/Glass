#pragma once

#include "pch.h"
#include "Core.h"
#include "Glass.h"

namespace Glass
{
	class GLASS_API Layer
	{
	protected:
		std::string m_Name;
		uint32_t m_ZIndex;

		Renderer LayerRenderer;
	public:
		Layer(std::string name, uint32_t index);
		virtual ~Layer() {}

		virtual void Update(float DeltaTime) {}
		virtual void Render() {}

		void SetZIndex(uint32_t zindex) { m_ZIndex = zindex; }
		void SetName(const std::string& layer_name) { m_Name = layer_name; }
		const std::string& GetName() { return m_Name; }

		uint32_t& GetZIndex() { return m_ZIndex; }
	};

	class GLASS_API LayerManager
	{
	public:
		static void PushLayer(std::shared_ptr<Layer> layer)
		{
			m_Layers.push_back(layer);
		}
		
		static void PopLayer()
		{
			m_Layers.pop_back();
		}

		static void RemoveLayer(int index)
		{
			m_Layers.erase(m_Layers.begin() + index);
		}

		static void SortLayers()
		{
			// an iterator is needed to swap specific elements
			std::vector<std::shared_ptr<Layer>>::iterator it;

			// local variables
			uint32_t i, j; // need to loop through the layer index's twice for the next and current value
			uint32_t first_index; // the first value checked 

			/*
				Iterator through the layer zindex's
			*/
			for (it = m_Layers.begin(); it != m_Layers.end(); ++it)
			{
				// through through the layers 
				for (i = 0; i < m_Layers.size(); ++i)
				{
					// set the first index to the current layers zindex
					first_index = m_Layers[i]->GetZIndex();

					// through through the layers again, getting the next layer after the first index/current layer (previous and next)
					for (j = i + 1; j < m_Layers.size(); ++j)
					{
						// check if the second index is less then the first
						if (m_Layers[j]->GetZIndex() < m_Layers[i]->GetZIndex())
						{
							// if so. then swap
							std::iter_swap(m_Layers[j], m_Layers[i]);
							LOG_INFO("Layers Swapped during Sorting Process");
						}
						// if not. then continue looping through the layers and checking the z index's
						else
							continue; // continue the for loop
					}
				}
			}

			// exit out of the function once done sorting
			return;
		}

		static std::vector<std::shared_ptr<Layer>>& GetLayers() 
		{
			return m_Layers;
		}
	private: 
		static std::vector<std::shared_ptr<Layer>> m_Layers;
	};
}



