#include "Plane.h"
#include "..\..\Dependencies\glm\glm\glm.hpp"
Plane Plane::Normalized() const
{
	float magnitude = mNormal.length();
	glm::vec3 unitNormal;
	unitNormal = glm::normalize(mNormal);
	return Plane(GetNormal(), mDistance/magnitude);
}
IntersectData Plane::IntersectSphere(const BoundingSphere & other) const
{
	// Finds distance of center of sphere from normal, Dot product is projection of sphere center on normal direction + how far along its own normal the plane is
	glm::vec3 unitNormal;
	unitNormal = glm::normalize(mNormal);
	float distancefromSphereCenter = fabs(glm::dot(unitNormal, other.GetCenter()) + mDistance);
	float distancefromSphere = distancefromSphereCenter - other.GetRadius();
	// If any distance at all between the two, doesn't intersect
	/*if (distancefromSphere < 0)
		std::cout << "Intersecting!\n";*/
	return IntersectData(distancefromSphere < 0, distancefromSphere);
}

IntersectData Plane::IntersectAABB(const BoundingBox & other) const
{
	
	glm::vec3 extense, center;
	center = (other.GetMaxExtends() + other.GetMinExtends())/2.0f;
	extense = other.GetMaxExtends() - center;
	float r = glm::dot(mNormal, extense);
	float s = glm::dot(mNormal, center) + mDistance;

	return IntersectData(s < r, 0, other.GetCenter() - mNormal);
}