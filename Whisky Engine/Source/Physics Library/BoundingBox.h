#ifndef AABB_H
#define AABB_H

#include <iostream>
#include "IntersectData.h"
#include "..\Component Library\Transform.h"
#include "..\Component Library\PhysicsComponent.h"
#include "Bounding.h"
#include "..\..\Dependencies\glm\glm\vec3.hpp"
class BoundingBox : public Bounding
{

private:
	const glm::vec3 minExtends;
	const glm::vec3 maxExtends;
	float halfWidth;
	float halfHeight;
	float halfDepth;
public:
	glm::vec3 mCenter;
	BoundingBox(const glm::vec3 & min, const glm::vec3 & max) :
	minExtends(min), maxExtends(max), halfWidth(0), halfHeight(0), halfDepth(0), Bounding(Bounding::AABB){}
	void SetCenter(const glm::vec3 & center) {
		Transform * t = static_cast<Transform *>(mOwner->GetOwner()->GetComponent<Transform>());
		halfWidth = t->GetScale().x / 2;
		halfHeight = t->GetScale().y / 2;
		halfDepth = t->GetScale().z / 2;
		mCenter = center;
	}
	IntersectData IntersectAABB(const BoundingBox& other) const;
	inline const glm::vec3 & GetCenter() { return mCenter; }
	inline const glm::vec3 & GetMinExtends() const { return minExtends; }
	inline const glm::vec3 & GetMaxExtends() const { return maxExtends; }
	inline const float GetHalfWidth() const { return halfWidth; }
	inline const float GetHalfHeight() const { return halfHeight; }
	inline const float GetHalfDepth() const { return halfDepth; }
};
#endif