#include "IntersectData.h"
#include "..\..\Dependencies\glm\glm\glm.hpp"
IntersectData::Direction IntersectData::SetDirection(glm::vec3 const & vector) const
{
	glm::vec3 Compass[] = {
		glm::vec3(0.0f, 1.0f, 0.0f), // UP
		glm::vec3(0.0, -1.0f, 0.0f), // DOWN
		glm::vec3(-1.0f, 0.0f, 0.0f),// LEFT
		glm::vec3(1.0f, 0.0f, 0.0f), // RIGHT
		glm::vec3(0.0f, 0.0f, 1.0f), // FRONT
		glm::vec3(0.0f, 0.0f, -1.0f) // BACK
	};
	glm::vec3 temp;
	temp = glm::normalize(vector);
	float max = 0.0f;
	int best_match = -1;
	for (int i = 0; i < 6; ++i)
	{
		float dotProduct = glm::dot(temp, Compass[i]);
		if (dotProduct > max)
		{
			max = dotProduct;
			best_match = i;
		}
	}

	return static_cast<IntersectData::Direction>(best_match);
}