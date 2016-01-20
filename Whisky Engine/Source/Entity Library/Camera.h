#pragma once

#define MAX_PITCH 90.0f
#define MAX_YAW 90.0f	// Not used but defined anyway
#define SENSITIVITY 0.01f

#include "..\Manager Library\FrameRateController.h"
#include "..\Manager Library\Input.h"
#include "..\Component Library\Component.h"
#include "..\..\Dependencies\GLEW\glew.h"
#include "..\..\Dependencies\glm\glm\gtc\matrix_transform.hpp"


class Camera
{
private:
	// VIEW MATRIX VARIABLES
	glm::vec3 CameraPos;
	glm::vec3 CameraDir;
	glm::vec3 UpVec;

	// EULER ANGLE VARIABLES
	glm::vec3 CurrentMousePos;
	glm::vec3 PrevMousePos;
	GLfloat CameraPitch; // Holds the current Pitch of the camera (rotation around Y axis)
	GLfloat CameraYaw;	 // Holds the current Yaw of the camera   (rotation around X axis)
	GLfloat Sensitivity; // Affects the camera sensitivity
	Input & InMan;
	FrameRateController & FrameMan;
public:
	// GETTERS
	glm::vec3 & GetCameraPos() { return CameraPos; }
	glm::vec3 & GetCameraDir(){ return CameraDir; }
	glm::vec3 & GetUpVec(){ return UpVec; }
	// SETTERS
	void SetCameraPos(float x, float y, float z) { CameraPos.x = x; CameraPos.y = y; CameraPos.z = z; }
	void SetCameraDir(float x, float y, float z) { CameraDir.x = x; CameraDir.y = y; CameraDir.z = z; }
	void SetUpVec(float, float, float, float);
	void Update();
	Camera();
	Camera(glm::vec3 const & eye, glm::vec3 const & target, glm::vec3 const & up, Input & in, FrameRateController & fr) : InMan(in), FrameMan(fr)
	{
		CameraPos = eye;
		CameraDir = target;
		UpVec = up;
		CameraPitch = 0.0f;
		CameraYaw = 0.0f;
		Sensitivity = SENSITIVITY;
	};
	
	virtual ~Camera();
};

