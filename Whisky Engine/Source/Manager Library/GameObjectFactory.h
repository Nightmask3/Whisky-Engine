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

#include "../Entity Library/GameObject.h"

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
	GameObject& Instantiate(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale = glm::vec3(1));
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

	bool InitializeArchetypes();
	bool InitializeLevel();

private:
	static GameObjectFactory* _pInstance;

	ObjVector	gameObjList_;
	NameObjMap	archetypeList_;

	int activeObjCount_;

	GameObject* pauseMenu_;
};

#endif