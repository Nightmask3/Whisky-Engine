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
#include "..\Component Library\Transform.h"
#include "..\Component Library\PlayerController.h"
#include "..\Manager Library\GameObjectFactory.h"
class Message;

class GameObject : public Entity
{
public:	// functions
	// ctor/dtor/operators
	GameObject(GameObjectFactory &);
	GameObject(GameObjectFactory & mFactory, const std::string& name);
	GameObject(GameObjectFactory & mFactory,const std::string& name, const std::string& tag);
	GameObject(const GameObject&);
	~GameObject();

	bool operator==(const GameObject&);

	// member functions
	void Update();
	void Relay(Message* m);
	inline void Activate()					{ isActive_ = true; }
	inline void Deactivate()				{ isActive_ = false; }

	// component functions
	template<typename ComponentName>	ComponentName* GetComponent() const;
	//template<typename ComponentName>	void AddComponent(ComponentName*);
	//template<typename ComponentName>	void RemoveComponent();
	void AddComponent(Component* comp);
	void RemoveComponent(unsigned);

	// Reference of handle is used to add to handle list of game object
	inline void AddHandle(Handle & handle)		 { Handles_.push_back(handle); }
	inline unsigned GetHandleID()				 { return handle_id_; }
	inline void		SetHandleID(unsigned int ID) { handle_id_ = ID; }
	//void Clone(GameObject&) const;

	// getters & setters
	inline bool IsActive() const			{ return isActive_; }
	inline const unsigned long ID() const	{ return id_; }
	inline std::string Name() const			{ return name_; }
	inline void Name(std::string n)			{ name_ = n; }
	inline GameObject* Pntr()				{ return this; }
	std::vector<HandleEntry_> & GetComponentList() { return HandleEntries_; }

	friend std::ostream& operator<<(std::ostream&, const GameObject&);
	
private:	// static members
	static unsigned long _last_id;
	
private:	// members

	unsigned int handle_id_;
	std::string name_, tag_;
	const unsigned long id_;
	bool isActive_;
	bool isArchetype_;

	GameObjectFactory& mFactoryRef_;
	std::vector<HandleEntry_> HandleEntries_;
	std::vector<Handle> Handles_;
};

////////////////////////////////////////////////////////////////
// template function definitions
////////////////////////////////////////////////////////////////

template<typename ComponentName>
ComponentName* GameObject::GetComponent() const
{
	// Request to Handle Manager for conversion of handle to pointer
	for(unsigned i = 0; i < Handles_.size(); ++i)
	{
		ComponentName comp;

		if (Handles_[i].m_type == comp.GetType())
			return static_cast<ComponentName *>(mFactoryRef_.ConvertHandletoPointer(Handles_[i], HandleEntries_));
	}
	std::cout << "Component not found!\n";
	return nullptr;
}

//template<typename ComponentName>
//void GameObject::AddComponent(ComponentName* c)
//{
//	//if (_componentList[T::Type])
//	// TODO : Replace with the call to Get function from Handle Manager 
//	if (
//	{
//
//#ifdef WARNINGS
//		std::cout << "====== WARNING: Trying to add second component of the same type to the Game Object!" << std::endl;
//#endif
//		//delete _componentList[T::Type];
//		delete componentList_[c->GetType()];
//
//	}
//
//		componentList_[c->GetType()] = static_cast<ComponentName*>(c);
//		c->SetOwner(this);
//}

//template<typename ComponentName>
//void GameObject::RemoveComponent()
//{
//	/*if (componentList_[ComponentName::Type])
//	{
//		delete componentList_[ComponentName::Type];
//	}*/
//}
#endif