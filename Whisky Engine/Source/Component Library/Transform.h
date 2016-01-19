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
		glm::vec3 mPosition_;			// Stores the translation matrix of the component
		glm::vec3 mRotation_;			// Stores the rotation matrix of the component
		glm::vec3 mScale_;				// Stores the scaling matrix of the component
	public:
		//Transform(); NOTE: Disabled as no need when there is an overriden version with default parameters, causes ambiguity
		void Position(glm::vec3 val)		
		{
			mPosition_ = val; 
		}
		// Adds the vector formed by x, y, z to the position
		void Position(float x, float y, float z)		
		{ 
			mPosition_ += glm::vec3(x, y, z);
		}
		// Sets the scale to the vector formed by x, y, z
		void Scale(float x, float y, float z) 
		{ 
			mScale_ = glm::vec3(x, y, z);
		}

		// Translates the position by the provided vector
		void Translate(glm::vec3 v)
		{
			mPosition_ += v;
		}

		// Creates a transform component according to a given set of vectors
		// Initializes rotation and position to (0, 0 ,0) and Scale to (1, 1, 1) as default parameters
		Transform(const glm::vec3 position = glm::vec3(0), const glm::vec3 rotation = glm::vec3(0), const glm::vec3 scale = glm::vec3(1));
		 ~Transform();
		// Returns the Model Transformation Matrix
		glm::mat4 ModelTransformationMatrix() const;
		
		void Update();
		static Transform * Deserialize(const char*);
};

