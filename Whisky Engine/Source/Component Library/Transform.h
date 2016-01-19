#pragma once
// C++ header files
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <sstream>
// GLM header files
#include "glm\mat4x4.hpp"
#include "glm\vec3.hpp"

// Component header files
#include "Component.h"
#include "..\..\Dependencies\GLEW\glew.h"
class Transform : public Component
{
	private:
		glm::vec3 mPosition;			// Stores the translation matrix of the component
		glm::vec3 mRotation;			// Stores the rotation matrix of the component
		glm::vec3 mScale;				// Stores the scaling matrix of the component
	public:
		// Inititalizes rotation and position to (0, 0 ,0) and Scale to (1, 1, 1)
		Transform();
		Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale);
		~Transform();
		
		// Scales the sprite along with its collider
		void ScaleWithCollider(float X, float Y, float Z);
		void Update();
		//static Transform * Deserialize(const char*);
};

