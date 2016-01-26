#pragma once
#include <vector>
// Manager Header files
#include "..\Manager Library\FrameRateController.h"
#include "..\Manager Library\EventManager.h"
// Component Header files
#include "..\Component Library\PhysicsComponent.h"
// Bounding box header file for types of bodies
#include "Bounding.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "Plane.h"
// How the handle manager refers to the physics system
#define PHYSICS_SYSTEM_TAG "Physics Manager"
class CollideEvent : public Event
{
	public:
	GameObject * mpObject1;
	GameObject * mpObject2;

	CollideEvent() : Event(COLLIDE) { mpObject1 = nullptr; mpObject2 = nullptr; }
	virtual ~CollideEvent() {}
};

class UnCollideEvent : public Event
{
public:
	GameObject * mpObject1;
	GameObject * mpObject2;

	UnCollideEvent() : Event(UNCOLLIDE) { mpObject1 = nullptr; mpObject2 = nullptr; }
	virtual ~UnCollideEvent() {}
};

class PhysicsManager
{
private:
	FrameRateController & frameManager_;
	GameObjectFactory & GOManager;
	static PhysicsManager * _pInstance;
	static int _mActiveComponentCount;
	std::vector<HandleEntry_> HandleEntries_;
	std::vector<Handle> Handles_;
public:
	bool bGameOver;
	//void SetBoundingBoxType(Bounding::RigidBodyType type);
	PhysicsManager(FrameRateController & frc, GameObjectFactory & gom) : frameManager_(frc), GOManager(gom){ bGameOver = false; }
	virtual ~PhysicsManager();
	// Physics management function
	void Simulation();
	void DetectCollision();
	void CheckCollision(Bounding const & shape1, Bounding const & shape2);
	void Resolution();
	void Update();
	bool Init();
	// Handle related functions
	inline void AddHandle(Handle & handle)		 { Handles_.push_back(handle); }
	inline void AddComponentToList(PhysicsComponent * comp) { AddHandle(GOManager.AddComponentToSystem(comp, Component::ComponentType::PHYSICS, HandleEntries_, _mActiveComponentCount, PHYSICS_SYSTEM_TAG)); _mActiveComponentCount++; }
	static PhysicsManager* Inst(FrameRateController &, GameObjectFactory &);
	std::vector<HandleEntry_> & GetComponentList() { return HandleEntries_; }

};

