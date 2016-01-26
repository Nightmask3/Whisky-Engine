#pragma once
#include "..\..\Dependencies\glm\glm\vec3.hpp"
class IntersectData
{
private:
	const bool mDoesIntersect;
	const float mDistance;
	const glm::vec3 mDifference;
public:
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FRONT,
		BACK
	};
	IntersectData::Direction mDirection;
	inline const bool & GetDoesIntersect() const { return mDoesIntersect; }
	inline const float & GetDistance() const { return mDistance; }
	inline const glm::vec3 & GetDifference() const { return mDifference; }
	inline Direction GetDirection() const { return mDirection; }
	Direction SetDirection(glm::vec3 const &) const;
	IntersectData(const bool does, const float dist, const glm::vec3 & vec = glm::vec3()) :
		mDoesIntersect(does),
		mDistance(dist),
		mDifference(vec)
	{}
};