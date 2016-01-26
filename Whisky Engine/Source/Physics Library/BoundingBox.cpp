#include "BoundingBox.h"
#include "..\..\Dependencies\glm\glm\glm.hpp"
IntersectData BoundingBox::IntersectAABB(const BoundingBox& other) const
{
	glm::vec3 distance1, distance2, distance;
	// If this AABB is closer to the origin
	distance1 = other.GetMinExtends() - maxExtends;
	// If the OTHER AABB is closer to the origin
	distance2 = minExtends - other.GetMaxExtends();
	// The actual distance vector is the larger distance between the AABBs
	distance = glm::greaterThan(distance1, distance2);
	float maxDistance = distance.x;
	if (distance.y > maxDistance)
		maxDistance = distance.y;
	if (distance.z > maxDistance)
		maxDistance = distance.z;
	// If there is some amount of space between the two on any axis, returns true, else false (I.E. intersection)
	if (maxDistance < 0)
		std::cout << "Intersection!\n";
	return IntersectData(maxDistance < 0, maxDistance);
}