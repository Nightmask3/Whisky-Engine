#include "Plane.h"
#include "..\..\Dependencies\glm\glm\glm.hpp"
Plane Plane::Normalized() const
{
	float magnitude = mNormal.length();
	glm::vec3 temp;
	temp = glm::normalize(mNormal);
	return Plane(GetNormal(), mDistance/magnitude);
}
IntersectData Plane::IntersectSphere(const BoundingSphere & other) const
{
	// Finds distance of center of sphere from normal, Dot product is projection of sphere center on normal direction + how far along its own normal the plane is
	glm::vec3 temp;
	temp = glm::normalize(mNormal);
	float distancefromSphereCenter = fabs(glm::dot(temp, other.GetCenter()) + mDistance);
	float distancefromSphere = distancefromSphereCenter - other.GetRadius();
	// If any distance at all between the two, doesn't intersect
	/*if (distancefromSphere < 0)
		std::cout << "Intersecting!\n";*/
	return IntersectData(distancefromSphere < 0, distancefromSphere);
}