#include "Bounding.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "Plane.h"
IntersectData Bounding::Intersect(const Bounding & other) const
{
	if (mType == Bounding::SPHERE && other.mType == Bounding::PLANE)
	{	
		// Get a read only reference to a Plane and Sphere to use for intersection
		const BoundingSphere self = static_cast<BoundingSphere const &>(*this);
		const Plane otherPlane = static_cast<Plane const &>(other);
		// Checks if plane and sphere are intersecting
		return otherPlane.IntersectSphere(self);
	}
	else if (mType == Bounding::AABB && other.mType == Bounding::SPHERE)
	{
		// Get a read only reference to Sphere and an AABB to use for intersection
		const BoundingBox self = static_cast<BoundingBox const &>(*this);
		const BoundingSphere otherSphere = static_cast<BoundingSphere const &>(other);
		// Checks if AABB and sphere are intersecting
		return otherSphere.IntersectAABB(self);
	}
	else if (mType == Bounding::SPHERE && other.mType == Bounding::SPHERE)
	{
		// Get a read only reference to Sphere and an AABB to use for intersection
		const BoundingSphere self = static_cast<BoundingSphere const &>(*this);
		const BoundingSphere otherSphere = static_cast<BoundingSphere const &>(other);
		// Checks if AABB and sphere are intersecting
		return otherSphere.IntersectBoundingSphere(self);
	}
	else if (mType == Bounding::AABB && other.mType == Bounding::PLANE)
	{
		// Get a read only reference to Sphere and an AABB to use for intersection
		const BoundingBox box = static_cast<BoundingBox const &>(*this);
		const Plane plane = static_cast<Plane const &>(other);
		// Checks if AABB and plane are intersecting
		return plane.IntersectAABB(box);
	}
	else if (mType == Bounding::PLANE && other.mType == Bounding::AABB)
	{
		// Get a read only reference to Sphere and an AABB to use for intersection
		const BoundingBox box = static_cast<BoundingBox const &>(other);
		const Plane plane = static_cast<Plane const &>(*this);
		// Checks if AABB and plane are intersecting
		return plane.IntersectAABB(box);
	}
	else if (mType == Bounding::AABB && other.mType == Bounding::AABB)
	{
		// Get a read only reference to both AABBs to use for intersection
		const BoundingBox boxOther = static_cast<BoundingBox const &>(other);
		const BoundingBox boxSelf = static_cast<BoundingBox const &>(*this);
		// Checks if AABB and plane are intersecting
		return boxSelf.IntersectAABB(boxOther);
	}
	/*std::cerr << "Error: Collisions not implemented between specified bounding shapes!\n";*/

	return IntersectData(false, 0);
}
void Bounding::UpdateCenter()
{
	if (mType == SPHERE)
	{
		BoundingSphere * sphere = nullptr;
		Transform * transform = nullptr;
		transform = mOwner->GetOwner()->GetComponent<Transform>();
		sphere = static_cast<BoundingSphere *>(this);
		glm::vec3 center;
		center = transform->GetPosition();
		sphere->SetCenter(center);
	}
	else if (mType == AABB)
	{
		BoundingBox * box = nullptr;
		Transform * transform = nullptr;
		transform = mOwner->GetOwner()->GetComponent<Transform>();
		box = static_cast<BoundingBox *>(this);
		glm::vec3 center;
		center = transform->GetPosition();
		box->SetCenter(center);
	}
}
Bounding::~Bounding()
{
}
