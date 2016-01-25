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
#include "..\OpenGLRenderer Library\Color.h"
#include <iostream>

enum MeshType
{
	QUAD = 0,
	CUBE,

	QUAD_WIREFRAME,
	BOX_COLLIDER_MESH,

	MESH_TYPE_COUNT
};

class Mesh : public Component
{
	public:	// static functions
		static Mesh* Deserialize(const char*);

	public:	// member functions
		Mesh(MeshType t);
		Mesh(MeshType t, Color c);
		Mesh();

		MeshType MeshHandle()		const { return mMeshHandle_; }
		bool	 IsActive()			const { return bIsActive_; }
		void	 SetActive(bool val)	  { bIsActive_ = val; }	
		Color	 GetColor()			const { return mColor_; }
		void	 SetColor(const Color& c) { mColor_ = c; }

private:	// data
		Color mColor_;		// might be stored in Material component/entity?
		MeshType mMeshHandle_;
		bool bIsActive_; 
};

#endif