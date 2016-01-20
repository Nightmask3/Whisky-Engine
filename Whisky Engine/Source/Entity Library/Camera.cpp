#include "Camera.h"

void Camera::Update()
{
	GLfloat cameraSpeed = 5.0f * FrameMan.Time();
	if (InMan.IsKeyPressed(sf::Keyboard::W))
	{
		// Forward Movement
		// Scales Target Vector by camera speed before adding to CameraPos
		CameraPos *= cameraSpeed;
		CameraPos += CameraDir;

	}
	if (InMan.IsKeyPressed(sf::Keyboard::A))
	{
		// Left Movement
		glm::vec3 RightVec;
		// Cross Product
		RightVec = glm::cross(CameraDir, UpVec);
		// Normalize target vector before scaling and subtracting from camera position
		RightVec = glm::normalize(RightVec);
		RightVec *= cameraSpeed;
		CameraPos - RightVec;
	}
	if (InMan.IsKeyPressed(sf::Keyboard::S))
	{
		// Backward Movement 
		glm::vec3 tempVector;
		tempVector = CameraDir * cameraSpeed;
		CameraPos -= tempVector;
	}
	if (InMan.IsKeyPressed(sf::Keyboard::D))
	{
		// Right Movement
		glm::vec3 RightVec;
		// Cross Product
		RightVec = glm::cross(CameraDir, UpVec);
		// Normalize before adding
		RightVec = glm::normalize(RightVec);
		CameraPos *= cameraSpeed;
		CameraPos += RightVec;
	}
	//PrevMousePos = InMan.GetMousePosition();
	// MOUSE UPDATE - EDITOR VIEW ONLY ALLOWS THIS WHEN RIGHT CLICK IS ACTIVATED AS WELL
//	if (InMan.isMouseButtonPressed(sf::Mouse::Right))
//	{
//		PrevMousePos = InMan.GetMousePosition();
//		CurrentMousePos = InMan.GetMousePosition();
//		GLfloat changeXPos, changeYPos;
//		changeXPos = CurrentMousePos.x - PrevMousePos.x;
//		changeYPos = PrevMousePos.y - CurrentMousePos.y; // Flipped as Y values range from bottom to top
//		PrevMousePos = CurrentMousePos;					 // Sets previous mouse Position to the current mouse position
//		// Affects the changes by sensitivity
//		changeXPos *= Sensitivity;
//		changeYPos *= Sensitivity;
//		// Affects the yaw and pitch
//		CameraYaw += changeXPos;
//		CameraPitch += changeYPos;
//		// Cap the pitch values to ensure non - weird movement
//		if (CameraYaw > MAX_PITCH)
//			CameraYaw = MAX_PITCH;
//		if (CameraYaw < -MAX_PITCH)
//			CameraYaw = -MAX_PITCH;
//		glm::vec3 temp;
//		temp.x = cosf(CameraPitch) * cosf(CameraYaw);
//		temp.y = sinf(CameraPitch);
//		temp.z = cosf(CameraPitch) * sinf(CameraYaw);
//		Vector3DNormalize(CameraDir, temp);
//	}
}


Camera::~Camera()
{
}
