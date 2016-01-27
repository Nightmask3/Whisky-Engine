#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::_pInstance = nullptr;
int PhysicsManager::_mActiveComponentCount = 0;
PhysicsManager::~PhysicsManager()
{
}
PhysicsManager* PhysicsManager::Inst(FrameRateController & frc, GameObjectFactory & gom)
{
	if (_pInstance == NULL)
	{
		_pInstance = new PhysicsManager(frc, gom);
	}
	return _pInstance;
}

bool PhysicsManager::Init()
{
	if (GOManager.InitializeListForSystem(HandleEntries_, PHYSICS_SYSTEM_TAG))
		return true;
	else
		return false;
}

void PhysicsManager::Update()
{
	// Three Stages
	// Simulation : Update the physics variables of all objects that have physics components (Apply gravity, velocity, forces etc.)
	Simulation();
	// Collision Detection : Checking every Physics Component that has a Rigid Body for collision against every other rigid body
	DetectCollision();
	// Resolution: Apply the physics values to the game object transforms
	Resolution();
}
void PhysicsManager::Simulation()
{
	PhysicsComponent * pSimulation = nullptr;
	// RK Integration - Using raw component pointer
	//while (frameManager_.ft_ > 0.0f)
	//{
	//	double deltatime = std::min(frameManager_.ft_, frameManager_.FrameTimeLimit());
	//	for (auto iterator = ComponentList_.begin(); iterator != ComponentList_.end(); ++iterator)
	//	{
	//		// Compute the change to the physics components of all objects, except those which are non - moving
	//		pSimulation = static_cast<PhysicsComponent*>(*iterator);
	//		/*if (pSimulation->GetMass() == 0.0f)
	//			continue;*/
	//		pSimulation->IntegrateRK4(frameManager_.GetTotalTime() , deltatime);
	//	}
	//	frameManager_.ft_ -= deltatime;
	//	frameManager_.AddtoTotalTime(deltatime);
	//}

	// RK Integration - Using handles
	//while (frameManager_.ft_ > 0.0f)
	//{
	//	double deltatime = std::min(frameManager_.ft_, frameManager_.FrameTimeLimit());
	//	for(auto iterator = Handles_.begin(); iterator != Handles_.end(); ++iterator)
	//	{
	//		// Compute the change to the physics components of all objects, except those which are non - moving
	//		pSimulation = static_cast<PhysicsComponent*>(GOManager.ConvertHandletoPointer(*iterator, HandleEntries_));
	//		/*if (pSimulation->GetMass() == 0.0f)
	//			continue;*/
	//		pSimulation->IntegrateRK4(frameManager_.GetTotalTime() , frameManager_.FrameTimeLimit());
	//	}
	//	frameManager_.ft_ -= deltatime;
	//	frameManager_.AddtoTotalTime(deltatime);
	//}

	// EULER Integration = Using raw component pointers
	for (auto iterator = ComponentList_.begin(); iterator != ComponentList_.end(); ++iterator)
	{
		// Compute the change to the physics components of all objects, except those which are non - moving
		pSimulation = static_cast<PhysicsComponent*>(*iterator);
		if (pSimulation->GetMass() == 0.0f)
			continue;
		pSimulation->IntegrateEuler(frameManager_.FrameDelta());
	}
}
void PhysicsManager::DetectCollision()
{
	PhysicsComponent * pCollisionDet1 = nullptr, *pCollisionDet2 = nullptr;
	// If only one object in world don't calculate
	if (Handles_.size() == 1)
		return;
	for (auto iterator1 = ComponentList_.begin(); iterator1 != ComponentList_.end(); ++iterator1)
	{
		pCollisionDet1 = static_cast<PhysicsComponent*>(*iterator1);

		for (auto iterator2 = iterator1 + 1; iterator2 != ComponentList_.end(); ++iterator2)
		{
			pCollisionDet2 = static_cast<PhysicsComponent*>(*iterator2);
			IntersectData data = pCollisionDet1->GetCollider().Intersect(pCollisionDet2->GetCollider());
			if (data.GetDoesIntersect())
			{
				if (pCollisionDet1->GetBoundingBox()->mType == Bounding::AABB && pCollisionDet2->GetBoundingBox()->mType == Bounding::SPHERE)
				{
					// If Spheres intersect with walls they should return to their last position
					float Penetration = 0.0f;
					BoundingSphere * sphere = static_cast<BoundingSphere *>(pCollisionDet2->GetBoundingBox());
					if (data.GetDirection() == IntersectData::LEFT || data.GetDirection() == IntersectData::RIGHT)
					{
						Penetration = sphere->GetRadius() - abs(data.GetDifference().x);
						// If Left collision, trying to move towards negative X direction, hence add
						if (data.GetDirection() == IntersectData::RIGHT)
						{
							pCollisionDet2->GetCurrentPosition().x += Penetration;
						}
						// And vice versa
						else
						{
							pCollisionDet2->GetCurrentPosition().x -= Penetration;
						}
					}
					else if (data.GetDirection() == IntersectData::UP || data.GetDirection() == IntersectData::DOWN)
					{
						Penetration = sphere->GetRadius() - abs(data.GetDifference().y);
						// If Up collision, trying to move towards negative Y direction, hence add
						if (data.GetDirection() == IntersectData::UP)
						{
							pCollisionDet2->GetCurrentPosition().y += Penetration;
						}
						// And vice versa
						else
						{
							pCollisionDet2->GetCurrentPosition().y -= Penetration;
						}
					}
					else if (data.GetDirection() == IntersectData::FRONT || data.GetDirection() == IntersectData::BACK)
					{
						Penetration = sphere->GetRadius() - abs(data.GetDifference().z);
						// If Front collision, trying to move towards negative Z direction, hence add
						if (data.GetDirection() == IntersectData::FRONT)
						{
							pCollisionDet2->GetCurrentPosition().z += Penetration;
						}
						// And vice versa
						else
						{
							pCollisionDet2->GetCurrentPosition().z -= Penetration;
						}
					}
					// Creates collision event
					CollideEvent collideEvent;
					collideEvent.mpObject1 = pCollisionDet1->GetOwner();
					collideEvent.mpObject2 = pCollisionDet2->GetOwner();
					// Makes the collided bodies handle it
					collideEvent.mpObject1->HandleEvent(&collideEvent);
					collideEvent.mpObject2->HandleEvent(&collideEvent);
				}
				else if (pCollisionDet1->GetBoundingBox()->mType == Bounding::SPHERE && pCollisionDet2->GetBoundingBox()->mType == Bounding::PLANE)
				{
					// If Spheres intersect with ground plane they should return to their last position, and no more acceleration or velocity along the Y axis
					//pCollisionDet1->mPositionCurr.y = pCollisionDet1->mPositionPrev.y;
					pCollisionDet1->GetVelocity().y = 0;
					pCollisionDet1->ToggleAcceleration(false);
					// Creates collision event
					CollideEvent collideEvent;
					collideEvent.mpObject1 = pCollisionDet1->GetOwner();
					collideEvent.mpObject2 = pCollisionDet2->GetOwner();
					// Makes the collided bodies handle it
					collideEvent.mpObject1->HandleEvent(&collideEvent);
					collideEvent.mpObject2->HandleEvent(&collideEvent);
				}
				else if (pCollisionDet1->GetBoundingBox()->mType == Bounding::SPHERE && pCollisionDet2->GetBoundingBox()->mType == Bounding::SPHERE)
				{
					// If Spheres intersect with another sphere
					// Creates collision event
					std::cout << "Colliding!";
					CollideEvent collideEvent;
					collideEvent.mpObject1 = pCollisionDet1->GetOwner();
					collideEvent.mpObject2 = pCollisionDet2->GetOwner();
					// Makes the collided bodies handle it
					collideEvent.mpObject1->HandleEvent(&collideEvent);
					collideEvent.mpObject2->HandleEvent(&collideEvent);
				}
				else if ((pCollisionDet1->GetBoundingBox()->mType == Bounding::AABB && pCollisionDet2->GetBoundingBox()->mType == Bounding::PLANE) || pCollisionDet1->GetBoundingBox()->mType == Bounding::PLANE && pCollisionDet2->GetBoundingBox()->mType == Bounding::AABB)
				{
					// If Boxes intersect with planes
					if (data.GetDoesIntersect() == true)
					{
						if (pCollisionDet1->GetBoundingBox()->mType == Bounding::AABB)
						{
							// Hack to stop things from falling for now, should use a boolean/bAcceleration later
							pCollisionDet1->SetMass(0);
						}
						else
						{
							pCollisionDet2->SetMass(0);
						}
					}
				}
				else if ((pCollisionDet1->GetBoundingBox()->mType == Bounding::AABB && pCollisionDet2->GetBoundingBox()->mType == Bounding::AABB) || pCollisionDet1->GetBoundingBox()->mType == Bounding::AABB && pCollisionDet2->GetBoundingBox()->mType == Bounding::AABB)
				{
					// If Boxes intersect with Boxes
					if (data.GetDoesIntersect() == true)
					{
						if (pCollisionDet1->GetBoundingBox()->mType == Bounding::AABB)
						{
							// Hack to stop things from falling for now, should use a boolean/bAcceleration later
							pCollisionDet1->SetMass(0);
							pCollisionDet2->SetMass(0);
						}
					}
				}
				
			}
			// Set bounding box color back to blue
			else 
			{
				UnCollideEvent DeCollideEvent;
				DeCollideEvent.mpObject1 = pCollisionDet1->GetOwner();
				DeCollideEvent.mpObject2 = pCollisionDet2->GetOwner();
				DeCollideEvent.mpObject1->HandleEvent(&DeCollideEvent);
				DeCollideEvent.mpObject2->HandleEvent(&DeCollideEvent);
				pCollisionDet1->ToggleAcceleration(true);
			}
		}
	}
}

void PhysicsManager::Resolution()
{
	PhysicsComponent * pSimulation = nullptr;

	for (auto iterator = ComponentList_.begin(); iterator != ComponentList_.end(); ++iterator)
	{
		// Compute the change to the physics components of all objects, except those which are non - moving
		pSimulation = static_cast<PhysicsComponent*>(*iterator);
		if (pSimulation->GetMass() == 0.0f)
			continue;
		pSimulation->UpdateTransform();
	}
}

