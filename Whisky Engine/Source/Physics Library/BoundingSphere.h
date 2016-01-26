#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include <iostream>
#include "..\..\Dependencies\glm\glm\vec3.hpp"
#include "Bounding.h"
#include "BoundingBox.h"
class BoundingSphere : public Bounding 
{
	private:
		glm::vec3 mCenter;
		const float mRadius;
	public:
		IntersectData IntersectBoundingSphere(const BoundingSphere & other) const;
		IntersectData IntersectAABB(const BoundingBox & other) const;
		inline const glm::vec3 & GetCenter() const { return mCenter; }
		inline const float & GetRadius() const { return mRadius; }
		inline void SetCenter(glm::vec3 const & vec) { mCenter = vec; };
		BoundingSphere(const glm::vec3 & cent, const float rad = 1.0f) : mCenter(cent), mRadius(rad), Bounding(SPHERE) { }
};
#endif