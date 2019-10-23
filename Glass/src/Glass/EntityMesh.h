#pragma once

#include "Mesh.h"

namespace Glass
{
	class GLASS_API EntityMesh : public Mesh
	{
	public:
		EntityMesh(glm::vec3 Position, int TextureIndex = 0);
		~EntityMesh();

		virtual void Tick(float DeltaTime) override;
		virtual void Render() override;
	private:
	};
}

