#include "EntityMesh.h"

namespace Glass
{
	EntityMesh::EntityMesh(glm::vec3 Position, int TextureIndex) :
		Mesh(Position, TextureIndex) {}
	EntityMesh::~EntityMesh() {}

	void EntityMesh::Tick(float DeltaTime)
	{
		Mesh::Tick(DeltaTime);
	}

	void EntityMesh::Render()
	{
		Mesh::Render();
	}
}