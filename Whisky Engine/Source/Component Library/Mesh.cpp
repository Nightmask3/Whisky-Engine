// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	Mesh.cpp
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/11/18
// Purpose			:	Class for mesh data for game object rendering
// History			:
// - 2015/11/18		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------


#include "Mesh.h"
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

const ComponentType Mesh::Type = MESH;

Mesh* Mesh::Deserialize(const char* params)
{
	Mesh* comp = NULL;

	string param = params;
	std::transform(param.begin(), param.end(), param.begin(), ::tolower);

	if (param == "quad")
		comp = new Mesh(QUAD);
	//else if (param == "")
	//	comp = new Mesh(???);

	else
	{
		cout << "Invalid argument creating mesh (" << param << ")" << endl;
	}

	return comp;
}

Mesh::Mesh(MeshType t) 
	: 
	_meshHandle(t),
	_isActive(true)
{}