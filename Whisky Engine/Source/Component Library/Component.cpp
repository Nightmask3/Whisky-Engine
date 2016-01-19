// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	Component.cpp
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/10/27
// Purpose			:	Base class for components to be used in game objects
// History			:
// - 2015/10/27		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#include "Component.h"

#include "..\Manager Library\utils.h"

#include <algorithm>
#include <iostream>

#define DEBUG1

Component* Component::CreateComponent(std::string name, const char* params)
{
	Component * comp = NULL;

	if (name == "transform")				comp = Transform::Deserialize(params);
	else if (name == "sprite")				comp = Sprite::Deserialize(params);
	else if (name == "mesh")				comp = Mesh::Deserialize(params);
	//else if (name == "selfdestruct")		comp = SelfDestruct::Deserialize(params);

	else std::cout << "WARNING: unknown component name when creating: " << name << std::endl;


	return comp;
}