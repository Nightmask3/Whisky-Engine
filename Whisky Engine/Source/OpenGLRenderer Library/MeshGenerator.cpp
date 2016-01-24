#include "MeshGenerator.h"
#include "Vertex.h"
#include "../Manager Library/Graphics.h"

//MeshData MeshGenerator::makeTriangle()
//{
//	MeshData mesh;
//	Vertex verts[] =
//	{
//		glm::vec3(+0.0f, +1.0f, +0.0f),
//		glm::vec3(+1.0f, +0.0f, +0.0f),
//
//		glm::vec3(-1.0f, -1.0f, +0.0f),
//		glm::vec3(+0.0f, +1.0f, +0.0f),
//
//		glm::vec3(+1.0f, -1.0f, +0.0f),
//		glm::vec3(+0.0f, +0.0f, +1.0f)
//	};
//
//	mesh.numVertices = sizeof(verts) / sizeof(*verts);
//	mesh.vertices = new Vertex[mesh.numVertices];
//	for (size_t i = 0; i < mesh.numVertices; i++)
//	{
//		mesh.vertices[i].position = verts[i].position;
//		mesh.vertices[i].color = verts[i].color;
//		std::cout << "pos: " << mesh.vertices[i].position.x << ", " <<
//			mesh.vertices[i].position.y << ", " <<
//			mesh.vertices[i].position.z << " " <<
//			std::endl;
//	}
//	//memcpy(mesh.vertices, verts, sizeof(verts));
//
//	GLuint indices[] = { 0, 1, 2 };
//	mesh.numIndices = sizeof(indices) / sizeof(*indices);
//	mesh.indices = new GLushort[mesh.numIndices];
//	for (size_t i = 0; i < mesh.numVertices; i++)
//	{
//		mesh.indices[i] = indices[i];
//	}
//	//memcpy(mesh.indices, indices, sizeof(indices));
//
//	return mesh;
//}