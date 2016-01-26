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

#define MaxGameObjects 4096
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
	GameObject& InstantiateEmpty();	// Consider removal? Don't want Game Objects that can exist without a transform/root component
	GameObject& InstantiateArchetype(const std::string&);
	GameObject& InstantiateArchetype(const std::string& name, const glm::vec3 & pos);
	// Initialize the position to (0,0,0), rotation to (0,0,0) and scale to (1,1,)
	GameObject& InstantiateExplicit(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale);
	void Destroy(GameObject&);

	std::pair<bool, GameObject*> Find(const std::string& name);

	GameObject& GetInactiveObject();	// friend function maybe?

	// getters & setters
	ObjVector& GameObjList();
	int GetActiveObjCount() const { return activeObjCount_; }
	GameObject*   GetMenu()	const { return pauseMenu_; }
	GameObject* GetPlayer() const { return _player; }
	void SetPlayer(GameObject* player) { _player = player; }
	GameObject* GetCamera() const { return _camera; }
	void SetCamera(GameObject* camera) { _camera = camera; }

	// Makes a call to handle manager to initialize component list for a game object
	bool InitializeListForGameObject(std::vector<HandleEntry_> & mEntries, int) const;

	// Makes a call to handle manager to initialize component list for a system
	bool InitializeListForSystem(std::vector<HandleEntry_> & mEntries, std::string) const;

	// Makes a call to handle manager to convert the handle to a pointer
	Component * ConvertHandletoPointer(Handle handle, std::vector<HandleEntry_> mEntries);

	// Adds a Component to a Game Object component list and returns the handle to it
	Handle AddComponent(void* p, unsigned int ,std::vector<HandleEntry_> & m_entries, std::string ComponentType, int index) const;
	Handle AddComponent(void* p, GameObject& obj) const;

	// For adding a component to a manager list
	Handle AddComponentToSystem(void* p, unsigned int, std::vector<HandleEntry_> & m_entries, unsigned int, std::string name);

	// Updates a Component
	bool UpdateComponent(Handle handle, void* p, std::vector<HandleEntry_> & m_entries);
	
	// Removes a Component
	bool Remove(Handle handle, std::vector<HandleEntry_> & m_entries, std::type_info const & CallerType);

	// Gets gameobject list
	ObjVector & GetObjectList() { return gameObjList_; }
private:

	GameObjectFactory();
	GameObjectFactory(const GameObjectFactory&){}
	GameObjectFactory& operator=(const GameObjectFactory&){}

	bool InitializeArchetypes();
	bool InitializeLevel();
private:
	static GameObjectFactory* _pInstance;
	static HandleManager* _pHandleMan;
	static int  _mGameObjectCounter;
	ObjVector	gameObjList_;
	NameObjMap	archetypeList_;
	
	GameObject *_player;
	GameObject *_camera;

	int activeObjCount_;
	
	GameObject* pauseMenu_;
};


#endif