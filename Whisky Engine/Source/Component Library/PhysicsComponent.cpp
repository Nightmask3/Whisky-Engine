
#include "..\Physics Library\BoundingSphere.h"
#include "..\Physics Library\BoundingBox.h"
#include "..\Physics Library\Plane.h"
#include "PhysicsComponent.h"

void PhysicsComponent::Serialize(std::string & Contents, unsigned int & Count)
{

}
void PhysicsComponent::Integrate(double t, double dt)
{
	Derivative a, b, c, d;
	mPositionPrev_ = mPositionCurr_;
	// Finds 4 derivatives
	a = Evaluate(t, 0.0f, Derivative());
	b = Evaluate(t, dt*0.5f, a);
	c = Evaluate(t, dt*0.5f, b);
	d = Evaluate(t, dt, c);
	// Finds weighted sum of derivatives for each:

	// Position from velocity
	float dxdt = 1.0f / 6.0f *
		(a.mDerivedVelocity.x + 2.0f*(b.mDerivedVelocity.x + c.mDerivedVelocity.x) + d.mDerivedVelocity.x);

	float dydt = 1.0f / 6.0f *
		(a.mDerivedVelocity.y + 2.0f*(b.mDerivedVelocity.y + c.mDerivedVelocity.y) + d.mDerivedVelocity.y);
	
	float dzdt = 1.0f / 6.0f *
		(a.mDerivedVelocity.z + 2.0f*(b.mDerivedVelocity.z + c.mDerivedVelocity.z) + d.mDerivedVelocity.z);
	// Velocity from acceleration
	float dvxdt = 1.0f / 6.0f *
		(a.mDerivedAcceleration.x + 2.0f*(b.mDerivedAcceleration.x + c.mDerivedAcceleration.x) + d.mDerivedAcceleration.x);

	float dvydt = 1.0f / 6.0f *
		(a.mDerivedAcceleration.y + 2.0f*(b.mDerivedAcceleration.y + c.mDerivedAcceleration.y) + d.mDerivedAcceleration.y);

	float dvzdt = 1.0f / 6.0f *
		(a.mDerivedAcceleration.z + 2.0f*(b.mDerivedAcceleration.z + c.mDerivedAcceleration.z) + d.mDerivedAcceleration.z);

	// Change position and velocity accordingly
	mPositionCurr_.x += dxdt * dt;
	mPositionCurr_.y += dydt * dt;
	mPositionCurr_.z += dzdt * dt;

	mVelocity_.x += dvxdt * dt;
	mVelocity_.y += dvydt * dt;
	mVelocity_.z += dvzdt * dt;
	// Cap the max velocity
	mVelocity_.y *= 0.99f;
}

void PhysicsComponent::UpdateTransform()
{
	Transform * t = mOwner_->GetComponent<Transform>();
	t->SetPosition(mPositionCurr_);
	if (pShape_->mType == Bounding::SPHERE)
	{
		BoundingSphere * s = static_cast<BoundingSphere *>(pShape_);
		s->SetCenter(mPositionCurr_);
	}
}

void PhysicsComponent::Recalculate()
{
	mVelocity_.x = mMomentum_.x * mInverseMass_;
	mVelocity_.y = mMomentum_.y * mInverseMass_;
	mVelocity_.z = mMomentum_.z * mInverseMass_;
}

PhysicsComponent::Derivative PhysicsComponent::Evaluate(double t, double dt, const Derivative &d)
{
	glm::vec3 positionTemp, velocityTemp;

	positionTemp = mPositionCurr_;
	positionTemp.x += d.mDerivedVelocity.x * dt;
	positionTemp.y += d.mDerivedVelocity.y * dt;
	positionTemp.z += d.mDerivedVelocity.z * dt;

	velocityTemp = mVelocity_;
	velocityTemp.x += d.mDerivedAcceleration.x * dt;
	velocityTemp.y += d.mDerivedAcceleration.y * dt;
	velocityTemp.z += d.mDerivedAcceleration.z * dt;
	
	Derivative output;
	output.mDerivedVelocity = velocityTemp;
	// If acceleration is turned off, do not calculate anymore
	if (bAcceleration_ == true)
		output.mDerivedAcceleration = Acceleration(t + dt);
	else
		output.mDerivedAcceleration = glm::vec3(0);
	return output;
}

glm::vec3 PhysicsComponent::Acceleration(float t)
{
	glm::vec3 output;
	output = glm::vec3(0);
	const float k = 0.2f;
	output.y = -k * t;
	// Caps the max falling speed
	if (abs(output.y) > 10)
		output.y = -10;
	return output;
}
void PhysicsComponent::SetBoundingBoxType(Bounding::RigidBodyType type)
{
	if (type == Bounding::SPHERE)
	{
		glm::vec3 center;
		center = mPositionCurr_;
		pShape_ = new BoundingSphere(center);
		pShape_->mOwner = this;
	}
	else if (type == Bounding::AABB)
	{
		glm::vec3 min, max;
		// Begin returns an iterator, Back returns an object 
		/*glm::vec3Set(&min, s->GetVertexList().begin()->X, s->GetVertexList().begin()->Y, s->GetVertexList().begin()->Z, 1);
		glm::vec3Set(&max, s->GetVertexList().back().X, s->GetVertexList().back().Y, s->GetVertexList().back().Z, 1);*/
		glm::vec3 center;
		center = mPositionCurr_;
		pShape_ = new BoundingBox(min, max);
		pShape_->mOwner = this;
		BoundingBox * b;
		b = static_cast<BoundingBox *>(pShape_);
		b->SetCenter(center);
	}
	else if (type == Bounding::PLANE)
	{
		pShape_ = new Plane(glm::vec3(0, 1, 0), -0.5); // Sets the origin plane as tile top
	}
}

void PhysicsComponent::HandleEvent(Event * pEvent)
{
	//// If a collide event
	//if (pEvent->mType == EventType::COLLIDE)
	//{
	//	// Change color values of bounding box to green
	//	for (int i = 0; i < VertexList.size(); i++)
	//	{
	//		if (mpShape_->mType == Bounding::AABB)
	//		{
	//			VertexList[i].G = 1;
	//			VertexList[i].A = 1;
	//		}
	//		else if (mpShape_->mType == Bounding::SPHERE)
	//		{
	//			VertexList[i].R = 1;
	//		}
	//	}
	//}
	//// If not colliding 
	//else if (pEvent->mType == EventType::UNCOLLIDE)
	//{
	//	for (int i = 0; i < VertexList.size(); i++)
	//	{
	//		
	//	/*	if (mpShape->mType == Bounding::AABB)
	//		{
	//			VertexList[i].G = 0;
	//			VertexList[i].R = 1;
	//			VertexList[i].A = 0.5;
	//		}*/
	//		if (mpShape_->mType == Bounding::SPHERE)
	//		{
	//			VertexList[i].B = 1;
	//			VertexList[i].R = 0;
	//		}
	//	}
	//}

}
