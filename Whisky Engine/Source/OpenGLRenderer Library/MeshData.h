#pragma once

#include <glew.h>
#include "Vertex.h"


struct MeshData
{
	MeshData() :
		vertices(NULL), numVertices(0),
		indices(NULL), numIndices(0) {}

	Vertex* vertices;	
	GLuint numVertices;	
	GLuint* indices;	// GLushort causes weird issues?
	GLuint numIndices;	

	GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}

	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLuint);
	}

	void CleanUp()
	{
		delete[] vertices;
		delete[] indices;
		numIndices = numVertices = 0;
	}
};

