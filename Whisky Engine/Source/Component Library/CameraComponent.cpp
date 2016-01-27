#include "CameraComponent.h"
#include "..\..\Engine.h"
#include "..\..\Dependencies\glm\glm\gtc\matrix_transform.hpp"

// Creates a camera component with given near, far, and view angle values
// Initializes near to 0.1f, far to 1000.0f, and angle to 45 degrees (PI/4) as a default
CameraComponent::CameraComponent(const float nr, const float fr, const float viewAngle) : Component(ComponentType::CAMERA_COMPONENT, "CameraComponent")
{
	_near = nr;
	_far = fr;
	_viewAngle = viewAngle;
}
CameraComponent::~CameraComponent()
{

}

// Returns the Projection Matrix
glm::mat4 CameraComponent::GetProjectionMatrix() const
{
	// Create View & Projection matrices
	// Width and height of window
	float width = (float) Engine::_resolution_w;
	float heigth = (float) Engine::_resolution_h;

	//glm::mat4 vProj =
	return glm::perspective(_viewAngle, width/heigth, _near, _far);
}


void CameraComponent::SetNear(float nr) { _near = nr; }
void CameraComponent::SetFar(float fr) { _far = fr; }
void CameraComponent::SetViewAngle(float viewAngle) { _viewAngle = viewAngle; }

void CameraComponent::Update(){

}
//static CameraComponent * Deserialize(const char*){}