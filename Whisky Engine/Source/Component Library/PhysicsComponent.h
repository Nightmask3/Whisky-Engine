#pragma once
#include "..\Manager Library\EventManager.h"
#include "..\Entity Library\GameObject.h"
#include "Transform.h"
#include "..\..\Dependencies\glm\glm\vec3.hpp"
#include "..\Physics Library\Bounding.h"
#include "..\OpenGLRenderer Library\MeshData.h"

class PhysicsComponent : public Component
{
private:
	/* -------- VARIABLES ---------- */
	struct Derivative
	{
		glm::vec3 mDerivedVelocity;
		glm::vec3 mDerivedAcceleration;
		Derivative()
		{
			mDerivedAcceleration = glm::vec3(0);
			mDerivedVelocity = glm::vec3(0);
		}
	};

	glm::vec3 mPositionCurr_;
	glm::vec3 mPositionPrev_;
	glm::vec3 mVelocity_;
	glm::vec3 mForce_;
	glm::vec3 mMomentum_;

	bool bIsPlayer_;
	bool bAcceleration_;
	float mMass_;
	float mInverseMass_;
	unsigned int system_handle_id_;
	unsigned int mLifeCount;
	MeshData mColliderMesh_;

	Bounding * pShape_; // Pointer to the bounding box to be used for this object
	
	
public:
	/* -------- FUNCTIONS ---------- */
	// GETTERS
	inline const Bounding & GetCollider() const { return static_cast<const Bounding &>(*pShape_); }
	inline float GetMass() { return mMass_; }
	inline float GetInversemass() { return mInverseMass_; }
	inline Bounding * GetBoundingBox() { return pShape_; }

	// Returns a reference to be able to change individual x,y,z values as opposed to setting a new position or translating as a whole
	inline glm::vec3 & GetCurrentPosition() { return mPositionCurr_; }
	inline glm::vec3 GetPreviousPosition() { return mPositionPrev_; }
	inline glm::vec3 & GetVelocity() { return mVelocity_; }

	// SETTERS
	inline void SetMass(float mass) { mMass_ = mass; mInverseMass_ = 1 / mMass_; }
	inline void SetCurrentPosition(glm::vec3 pos) { mPositionCurr_ = pos; }
	inline void TranslatePosition(glm::vec3 pos) { mPositionCurr_ += pos; }
	inline void SetVelocity(glm::vec3 vel) { mVelocity_ = vel; }
	inline void ToggleAcceleration(bool value) { bAcceleration_ = value; }
	void Update() {}
	void Serialize(std::string & Contents, unsigned int & Count);
	void UpdateTransform();
	void Recalculate();
	void IntegrateRK4(double totalTime, double dt);
	void IntegrateEuler(float deltaTime);
	void HandleEvent(Event *);
	void SetBoundingBoxType(Bounding::RigidBodyType type);
	Derivative Evaluate(double t, double dt, const Derivative &);
	glm::vec3 Acceleration(float t);

	PhysicsComponent() : Component(Component::PHYSICS, "Physics")
	{
		mVelocity_ = glm::vec3(0);
		mPositionCurr_ = glm::vec3(0);
		mPositionPrev_ = glm::vec3(0);
		mMomentum_ = glm::vec3(0);
		mForce_ = glm::vec3(0);
		mMass_ = 1.0f;
		mInverseMass_ = 0.0f;
		bAcceleration_ = true;
		bIsPlayer_ = false;
		mLifeCount = 3;
	}
	~PhysicsComponent(){}
};

