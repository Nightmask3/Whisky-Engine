#include "MeshGenerator.h"
#include "Vertex.h"
#include "../Manager Library/Graphics.h"

MeshData MeshGenerator::MakeTriangle()
{
	MeshData mesh;
	Vertex verts[] =
	{
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),

		glm::vec3(-1.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),

		glm::vec3(+1.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f)
	};

	mesh.numVertices = sizeof(verts) / sizeof(*verts);
	mesh.vertices = new Vertex[mesh.numVertices];
	memcpy(mesh.vertices, verts, sizeof(verts));

	GLuint indices[] = { 0, 1, 2 };
	mesh.numIndices = sizeof(indices) / sizeof(*indices);
	mesh.indices = new GLuint[mesh.numIndices];
	memcpy(mesh.indices, indices, sizeof(indices));

	return mesh;
}