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
class TransformComponent : public Component(Component::TRANSFORM)
{
	private:
		glm::vec3 mPosition;			// Stores the translation matrix of the component
		glm::vec3 mRotation;			// Stores the rotation matrix of the component
		glm::vec3 mScale;				// Stores the scaling matrix of the component
	public:
		// Inititalizes rotation and position to (0, 0 ,0) and Scale to (1, 1, 1)
		TransformComponent();
		TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		~TransformComponent();
		
		// Scales the sprite along with its collider
		void ScaleWithCollider(float X, float Y, float Z);
		void Update();
		static TransformComponent * Deserialize(const char*);
};

