#include "EntityMesh.h"

namespace Glass
{
	EntityMesh::EntityMesh(glm::vec3 Position, int TextureIndex) :
		Mesh(Position, TextureIndex) {}
	EntityMesh::~EntityMesh() 
	{
		SetObjectType(STATIC_SPRITE);
	}

	void EntityMesh::Tick(float DeltaTime)
	{
		Mesh::Tick(DeltaTime);
	}

	void EntityMesh::Render()
	{
		Mesh::Render();
	}
}