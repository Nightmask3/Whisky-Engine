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
class TransformComponent : public Component
{
	public:
		glm::vec3 mPosition;			// Stores the translation matrix of the component
		glm::vec3 mRotation;			// Stores the rotation matrix of the component
		glm::vec3 mScale;				// Stores the scaling matrix of the component
	public:
		TransformComponent() : Component(ComponentType::TRANSFORM){ 
			mPosition = mRotation = glm::vec3(0, 0, 0);  
			mScale = glm::vec3(1); 
		}
		~TransformComponent();
		void Translate(float X, float Y, float Z);
		void Rotate(float AngleX, float AngleY, float AngleZ);
		void Scale(float X, float Y, float Z);
		// Scales the sprite along with its collider
		void ScaleWithCollider(float X, float Y, float Z);
		void Update();
		void Serialize(std::string &, unsigned int &);
};

