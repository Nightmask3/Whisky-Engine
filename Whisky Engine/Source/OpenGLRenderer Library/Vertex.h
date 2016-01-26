#pragma once

//#include "..\..\Dependencies\"

#include "..\..\Dependencies\glm\glm\glm.hpp"

//const GLuint NUM_VERT_PER_TRI = 3;
//const GLuint NUM_FLOAT_PER_VERT = 3;
//const GLuint TRI_SIZE = NUM_VERT_PER_TRI * NUM_FLOAT_PER_VERT * sizeof(float);
//
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};
