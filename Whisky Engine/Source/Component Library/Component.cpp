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

#include "Components.h"
#include <algorithm>
#include <iostream>

#define DEBUG1

Component* Component::CreateComponent(std::string name)
{
	Component * comp = NULL;

	if (name == "transform")				//comp = Transform::Deserialize(params);
	{
		comp = new Transform();
	}
	//else if (name == "sprite")				//comp = Sprite::Deserialize(params);
	//{
	//	comp = new Sprite();
	//}
	else if (name == "mesh")				//comp = Mesh::Deserialize(params);
	{
		comp = new Mesh(MeshType::QUAD);
	}
	//else if (name == "selfdestruct")		comp = SelfDestruct::Deserialize(params);

	else std::cout << "WARNING: Trying to create an unknown type of component: " << name << std::endl;


	return comp;
}

Component* Component::DeSerializeComponent(std::string name, const char* params)
{
	// relevant SO question
	// http://stackoverflow.com/questions/582331/is-there-a-way-to-instantiate-objects-from-a-string-holding-their-class-name
	
	Component * comp = NULL;
	if (name == "transform")				comp =		  Transform::Deserialize(params);
	else if (name == "mesh")				comp =			   Mesh::Deserialize(params);
	else if (name == "sprite")				comp =			 Sprite::Deserialize(params);
	else if (name == "playercontroller")	comp = PlayerController::Deserialize(params);
	
	else std::cout << "WARNING: Trying to create an unknown type of component: " << name << std::endl;

	return comp;
}