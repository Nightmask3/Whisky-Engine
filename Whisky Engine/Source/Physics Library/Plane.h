#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "Bounding.h"
#include "BoundingSphere.h"
#include "..\..\Dependencies\glm\glm\vec3.hpp"

class Plane : public Bounding
{
private:
	const glm::vec3 mNormal;
	const float mDistance;
public:
	Plane(const glm::vec3 & Normal, float dist) :
		mNormal(Normal),
		mDistance(dist), Bounding(Bounding::PLANE){}
	IntersectData IntersectSphere(const BoundingSphere & other) const;
	inline const glm::vec3 & GetNormal() const { return mNormal; }
	inline const float GetDistance() const { return mDistance; }
	Plane Normalized() const;
};
#endif