// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	GameObject.h
// Author			:	Team Stake
// Creation Date	:	2016/01/17
// Purpose			:	Class for encapsulating game object related data
// History			:
// - 2016/01/17		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

#include "Entity.h"
#include "..\Component Library\Component.h"
#include "..\Component Library\TransformComponent.h"
#include "..\Component Library\PlayerController.h"
class Message;
class GameObject : public Entity
{
public:
	// ctor/dtor/operators
	GameObject();
	GameObject(const std::string& name);
	GameObject(const std::string& name, const std::string& tag);
	GameObject(const GameObject&);
	~GameObject();

	bool operator==(const GameObject&);

	// member functions
	void Update();
	void Relay(Message* m);

	template<typename ComponentName>	ComponentName* GetComponent() const;
	template<typename ComponentName>	void AddComponent(ComponentName*);
	template<typename ComponentName>	void RemoveComponent();
	void RemoveComponent(unsigned);

	void Clone(GameObject&) const;

	// getters & setters
	inline bool IsActive() const			{ return isActive_; }
	inline void Activate()					{ isActive_ = true; }
	inline void Deactivate()				{ isActive_ = false; }
	inline const unsigned long ID() const	{ return id_; }
	inline std::string Name() const			{ return name_; }
	inline void Name(std::string n)			{ name_ = n; }
	inline GameObject* Pntr()				{ return this; }

	friend std::ostream& operator<<(std::ostream&, const GameObject&);

	bool IsArchetype() const { return isArchetype_; }
	void IsArchetype(bool val) { isArchetype_ = val; }

	// static members
private:
	static unsigned long _last_id;

	// members
private:

	std::string name_, tag_;
	const unsigned long id_;
	bool isActive_;
	bool isArchetype_;

	std::vector<unsigned int> componentHandles;

	std::vector<Component *> componentList_;

};

////////////////////////////////////////////////////////////////
// template function definitions
////////////////////////////////////////////////////////////////

template<typename ComponentName>
ComponentName* GameObject::GetComponent() const
{
	return static_cast<ComponentName*>(componentList_[ComponentName::Type]);
}

template<typename ComponentName>
void GameObject::AddComponent(ComponentName* c)
{
	//if (_componentList[T::Type])
	if (componentList_[c->GetType()])
	{

#ifdef WARNINGS
		std::cout << "====== WARNING: Trying to add second component of the same type to the Game Object!" << std::endl;
#endif

		//delete _componentList[T::Type];
		delete componentList_[c->GetType()];

	}

		componentList_[c->GetType()] = static_cast<ComponentName*>(c);
		c->SetOwner(this);
}

template<typename ComponentName>
void GameObject::RemoveComponent()
{
	if (componentList_[ComponentName::Type])
	{
		delete componentList_[ComponentName::Type];
	}
}
#endif