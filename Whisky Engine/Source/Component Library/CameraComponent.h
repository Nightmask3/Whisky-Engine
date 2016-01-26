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
#define PI 3.1415926

class CameraComponent : public Component
{
private:
	float _near, _far;
	float _viewAngle;
	glm::mat4 _viewMatrix; // to be removed (after camera component)

public:
	// Creates a camera component with given near, far, and view angle values
	// Initializes near to 0.1f, far to 1000.0f, and angle to 45 degrees (PI/4) as a default
	CameraComponent(const float near = 0.1f, const float far = 1000.0f, const float viewAngle = PI/4 );
	~CameraComponent();
	
	void SetNear(float near);
	void SetFar(float far);
	void SetViewAngle(float viewAngle);

	// Returns the Projection Matrix
	glm::mat4 GetProjectionMatrix() const;

	void Update();
	static const ComponentType _mType = Component::CAMERA_COMPONENT;
	//static CameraComponent * Deserialize(const char*);
};

