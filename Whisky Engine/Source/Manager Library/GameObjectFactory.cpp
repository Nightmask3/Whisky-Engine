// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	GameObjectManager.cpp
// Author			:	Team Stake
// Creation Date	:	2015/10/27
// Purpose			:	Manager system for handling game objects 
// History			:
// - 2015/10/27		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#include "..\..\Engine.h"

#include <string>
#include <functional>
#include <cctype>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <..\Component Library\Components.h>


using std::cout;
using std::endl;
using std::stringstream;
using std::string;

#define NO_DEBUG

	///////////////////////////////////////////////////////////////////////////////////////////////
	// static functions
	///////////////////////////////////////////////////////////////////////////////////////////////

	GameObjectFactory* GameObjectFactory::_pInstance = NULL;
	GameObjectFactory* GameObjectFactory::Inst()
	{
		if (_pInstance == NULL) _pInstance = new GameObjectFactory();

		return _pInstance;
	}


	GameObjectFactory::GameObjectFactory()
	{
		// Creates a handle manager and gives it the reference to this game object factory for future use
		_pHandleMan = new HandleManager(*_pInstance);

	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	// system functions
	///////////////////////////////////////////////////////////////////////////////////////////////

	bool GameObjectFactory::Init()
	{
		cout << "GameObjectManager System is initialized with " << gameObjList_.capacity() << " game objects" << endl;
		return true;
	}

	bool GameObjectFactory::Load()
	{
		if (!InitializeArchetypes() ||
			!InitializeLevel()
			)
			return false;
		return true;
	}

	void GameObjectFactory::Update()
	{	
		// update every active object
		activeObjCount_ = 0;
		for (auto& obj : gameObjList_)
			if (obj.IsActive())
			{
				obj.Update();
				activeObjCount_++;
			}

		// update UI
		//std::pair<bool, GameObject*> result = Find("Player");
		//if (result.first)
		//{
		//	GameObject* player = result.second;
		//	if ((result = Find("HealthBar")).first)
		//	{
		//		GameObject* hpBar = result.second;
		//		if ((result = Find("WeaponBar")).first)
		//		{
		//			GameObject* weaponBar = result.second;

		//			// all ui elements are found.
		//			//if (!player->GetComponent<PlayerController>) cout << "NULL PLAYER!" << endl;
		//			float hp = static_cast<float>(player->GetComponent<PlayerController>()->Hp());
		//			float wp = static_cast<float>(player->GetComponent<PlayerController>()->WeaponCharge());
		//			int lvl = 1 + player->GetComponent<PlayerController>()->WeaponLevel();

		//			// health bar original scales: (7.5, 0.8)
		//			hpBar->GetComponent<Transform>()->Scale((hp / 10)*7.5f, 0.8f);

		//			// health bar original scales: (7.5, 0.8)
		//			weaponBar->GetComponent<Transform>()->Scale((wp / lvl)*8.0f, 0.8f);


		//		}

		//	}
		//}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Member functions
	///////////////////////////////////////////////////////////////////////////////////////////////
	bool GameObjectFactory::InitializeArchetypes()
	{
		for (const auto archetype_s : RSC->GetArchetypeList())
		{
			archetypeList_[archetype_s.name].Name(archetype_s.name);
			archetypeList_[archetype_s.name].IsArchetype(true);
			for (auto& component_s : archetype_s.componentList)
			{
				// grab the component name and parameters
				string	componentName = component_s.first;
				const char* params = component_s.second.c_str();

				// lowercase the component name
				//std::Transform(componentName.begin(), componentName.end(), componentName.begin(), ::tolower);

				// create the component and add it to the Gameobject instance
				Component* component = Component::CreateComponent(componentName, params);
				if (component)	archetypeList_[archetype_s.name].AddComponent(component);
				else
				{
					cout << "Error creating component for archetype " << archetypeList_[archetype_s.name].Name() << ": " << componentName << endl;
					return false;
				}
			}
		}
		return true;
	}

	bool GameObjectFactory::InitializeLevel()
	{
		// get the level data from the resource manager
		auto objList = RSC->GetLevelData();

		// Deserialize the objects in the level data
		for (auto& obj_s : objList)
		{
			// instantiate every object in the scene
			GameObject& obj = Instantiate();
			obj.Name(obj_s.name);
			auto components_s = obj_s.componentList;

			// for every component in the gameobject's component list
			for (auto& component_s : components_s)
			{
				// grab the component name and parameters
					 string componentName	= component_s.first;
				const char* params			= component_s.second.c_str();



				// create the component and add it to the gameobject instance
				Component* component = Component::CreateComponent(componentName, params);
				if (component)
				{
					// TODO: overhaul here, replace with handle manager.
					obj.AddComponent(component);

				}
				else
				{
					cout << "Error creating component: " << componentName << endl;
					return false;
				}
			}

			if (obj.Name() == "PauseMenu")
			{
				pauseMenu_ = obj.Pntr();
			}
		}
		std::vector<HandleEntry_> vec;

		InitializeList(vec, typeid(GameObjectFactory));
		
		return true;
	}
	// Initializes a list using a reference to the container of the system that called this function
	bool GameObjectFactory::InitializeList(std::vector<HandleEntry_> & mEntries, type_info const & CallerType)
	{
		_pHandleMan->InitializeList(mEntries, CallerType);
	}
	std::vector<GameObject>& GameObjectFactory::GameObjList()
	{
		return gameObjList_;
	}

	GameObject& GameObjectFactory::InstantiateExplicit(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale)
	{
		// TODO: Fix warning: not all paths return a value
		for (auto& obj : gameObjList_)
		{
			if (!obj.IsActive())
			{
				obj.Activate();
				obj.AddComponent(new Transform(position, rotation, scale));
				return obj;
			}
		}

		cout << "WARNING: MAX GAME OBJECTS REACHED" << endl;
		return gameObjList_.back();
	}

	GameObject& GameObjectFactory::Instantiate()
	{
		// TODO: Fix warning: not all paths return a value
		for (auto& obj : gameObjList_)
		{
			if (!obj.IsActive())
			{
				obj.Activate();

				obj.AddComponent(new Transform());
				return obj;
			}
		}

		cout << "WARNING: MAX GAME OBJECTS REACHED" << endl;
		return gameObjList_.back();
	}

	GameObject& GameObjectFactory::InstantiateArchetype(const std::string & name)
	{
		for (auto& obj : gameObjList_)
		{
			if (!obj.IsActive())
			{
				archetypeList_[name].Clone(obj);
				return obj;
			}
		}

		cout << "WARNING: " << __FUNCTION__ << " MAX GAME OBJECTS REACHED" << endl;
		return gameObjList_.back();
	}

	GameObject& GameObjectFactory::InstantiateArchetype(const std::string & name, const glm::vec3 & pos)
	{
		for (auto& obj : gameObjList_)
		{
			if (!obj.IsActive())
			{
				archetypeList_[name].Clone(obj);
				obj.GetComponent<Transform>()->Position(pos);
				return obj;
			}
		}

		cout << "WARNING: " << __FUNCTION__ << " MAX GAME OBJECTS REACHED" << endl;
		return gameObjList_.back();
	}
	bool AddComponent(std::vector<HandleEntry_> & m_entries, type_info const & CallerType)
	{

	}
	void GameObjectFactory::Destroy(GameObject& obj)
	{
		if (!obj.IsActive()) return;

		// remove all components
		for (size_t i = 1; i < Component::ComponentType::COMPONENT_COUNT; i++)
			obj.RemoveComponent(i);
		obj.Deactivate();
	}

	std::pair<bool, GameObject*> GameObjectFactory::Find(const std::string& name)
	{
		bool found = false;
		GameObject& retObj = gameObjList_.back();

		for (GameObject& obj : gameObjList_)
		{
			if (obj.IsActive() && obj.Name() == name)
			{
				return std::make_pair(true, obj.Pntr());
			}
		}

		return std::make_pair(found, retObj.Pntr());
	}

	GameObject& GameObjectFactory::GetInactiveObject()
	{
		GameObject& defaultObj = gameObjList_.back();
		for (auto& obj : gameObjList_)
		{
			if (!obj.IsActive())
			{
				return obj;
			}
		}

		cout << "WARNING: GameObjectManager::GetInactiveObject(): GameObjectList is full!" << endl;
		return defaultObj;
	}