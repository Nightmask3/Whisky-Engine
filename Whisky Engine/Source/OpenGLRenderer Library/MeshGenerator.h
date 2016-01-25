#pragma once

#include "MeshData.h"

class MeshGenerator
{
public:
	static MeshData MakeTriangle();
	static MeshData MakeCube();
	static const GLsizei CubeIndexCount = 6;
	static const GLsizei TriIndexCount = 3;
};

