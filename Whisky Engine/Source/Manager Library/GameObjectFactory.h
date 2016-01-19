// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	GameObjectManager.h
// Author			:	Team Stake
// Creation Date	:	2016/1/14
// Purpose			:	Wrapper class for game engine main systems
// History			:
// - 2016/1/14		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "..\Entity Library\GameObject.h"
#include "HandleManager.h"

#include <vector>
#include <map>


class GameObjectFactory
{
	typedef std::vector<GameObject>				ObjVector;
	typedef std::map<std::string, GameObject>	NameObjMap;

public:
	static GameObjectFactory* Inst();

	// system functions
	bool Init();
	bool Load();
	void Update();


	// member functions
	GameObject& Instantiate();		// Consider removal? Don't want Game Objects that can exist without a transform/root component
	GameObject& InstantiateArchetype(const std::string&);
	GameObject& InstantiateArchetype(const std::string& name, glm::vec3 & pos);
	// Initialize the position to (0,0,0), rotation to (0,0,0) and scale to (1,1,)
	GameObject& Instantiate(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale = glm::vec3(1));
	void Destroy(GameObject&);

	std::pair<bool, GameObject*> Find(const std::string& name);

	GameObject& GetInactiveObject();	// friend function maybe?

	// getters & setters
	ObjVector& GameObjList();
	int GetActiveObjCount() const { return activeObjCount_; }
	GameObject*   GetMenu()	const { return pauseMenu_; }

private:
	GameObjectFactory();
	GameObjectFactory(const GameObjectFactory&){}
	GameObjectFactory& operator=(const GameObjectFactory&){}

	bool InitializeArchetypes(const std::string & name, const glm::vec3 & pos);
	bool InitializeLevel();
	// Makes a call to handle manager to initialize list
	bool InitializeList(std::vector<HandleEntry_> & mEntries, type_info const & CallerType);
	// Adds an Object
	bool AddObject(void* p, uint32 type, std::vector<HandleEntry_> & m_entries, type_info const & CallerType);
	// Updates an Object
	bool UpdateObject(Handle handle, void* p, std::vector<HandleEntry_> & m_entries);
	// Removes an Object
	bool Remove(Handle handle, std::vector<HandleEntry_> & m_entries, type_info const & CallerType);
	template <typename T> 
	bool CreateComponent()	// Member Template function used to create component of any type
	{
		Component * mComponent = nullptr;
		// Create component type as requested
		if (typeid(T) == typeid(TransformComponent))
		{
			
			return true;
		}
		else if (typeid(T) == typeid(Mesh))
		{
			return true;
		}
		else if (typeid(T) == typeid(PlayerController))
		{
			
			return true;
		}
		else if (typeid(T) == typeid(PhysicsComponent))
		{
			mComponent = new PhysicsComponent();
			mComponent->mOwner = &(ObjectLibrary.back());
			mComponent->mOwner->ComponentListSize++;
			mComponent->mOwner->ComponentList.push_back(mComponent);
			// Sets current position to use in physics simulation
			TransformComponent * t = nullptr;
			t = static_cast<TransformComponent *>(mComponent->mOwner->GetComponent(Component::TRANSFORM));

			PhysicsComponent * p = nullptr;
			p = static_cast<PhysicsComponent *>(mComponent->mOwner->GetComponent(Component::PHYSICS));

			Vector3DSet(&(p->mPositionCurr), t->mTranslation.m[0][3], t->mTranslation.m[1][3], t->mTranslation.m[2][3], 1);
			PhyManager.PhysicsObjectsList.push_back(mComponent);
			return true;
		}
		else if (typeid(T) == typeid(BehaviorComponent))
		{
			return true;
		}
		/* TODO : Add more component types here */
		else
		{
			std::cout << "Component Type not currently implemented OR Invalid Component Type." << std::endl;
		}
		return false;
	}
private:
	static GameObjectFactory* _pInstance;
	static HandleManager* _pHandleMan;

	ObjVector	gameObjList_;
	NameObjMap	archetypeList_;

	int activeObjCount_;

	GameObject* pauseMenu_;
};

#endif