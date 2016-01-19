// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	Mesh.h
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

#ifndef MESH_H
#define MESH_H

#include "Component.h"

#include <iostream>

enum MeshType
{
	QUAD = 0,

	QUAD_WIREFRAME,
	BOX_COLLIDER_MESH,

	MESH_TYPE_COUNT
};


class Mesh : public Component
{
	public:
		static Mesh* Deserialize(const char*);

	public:
		Mesh(MeshType);

		MeshType MeshHandle() const { return mMeshHandle_; }
		bool IsActive() const		{ return bIsActive_; }
		void SetActive(bool val)	{ bIsActive_ = val; }

	private:
		MeshType mMeshHandle_;
		bool bIsActive_; 
};

#endif