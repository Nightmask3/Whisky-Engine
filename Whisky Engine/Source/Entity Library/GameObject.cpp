// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	GameObject.cpp
// Author			:	Team Stake
// Creation Date	:	2015/10/25
// Purpose			:	Class for encapsulating game object related data
// History			:
// - 2015/10/25		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#include "..\..\Engine.h"
#include <sstream>
#include "..\Manager Library\GameObjectFactory.h"
#include <cassert>
#include "..\Component Library\Sprite.h"

using std::cout; 
using std::endl;
using std::string;

#define DEBUG1

const unsigned long id_offset = 1000ul;
unsigned long GameObject::_last_id = id_offset;

///////////////////////////////////////////////////////////////////////////////
// ctor/dtor/operator
///////////////////////////////////////////////////////////////////////////////

GameObject::GameObject(GameObjectFactory & mFactory)
	: isActive_(false), 
	  isArchetype_(false), 
	  id_(_last_id++), 
	  mFactoryRef_(mFactory), 
	  Entity(EntityType::GameObject)
	{
		name_ = string("GameObject") + std::to_string(id_ - id_offset);
		tag_ = string("None");
		//componentList_.resize(Component::ComponentType::COMPONENT_COUNT, NULL);


#ifdef DEBUG
		cout << "gameobj ctor: " << id_ << "\t: " << name_ << "(" << tag_ << ")" << endl;
#endif
	}

GameObject::GameObject(GameObjectFactory & mFactory, const string& name)
		:
		name_(name),
		tag_("None"),
		id_(_last_id++),
		isActive_(false),
		isArchetype_(false),
		mFactoryRef_(mFactory),
		Entity(EntityType::GameObject)
	{
		//componentList_.resize(Component::ComponentType::COMPONENT_COUNT, NULL);

#ifdef DEBUG
		cout << "gameobj ctor(str): " << id_ << "\t: " << name_ << "(" << tag_ << ")" << endl;
#endif
	}

GameObject::GameObject(GameObjectFactory & mFactory, const string& name, const string& tag)
		:
		name_(name),
		tag_(tag),
		id_(_last_id++),
		isActive_(false),
		isArchetype_(false),
		mFactoryRef_(mFactory),
		Entity(EntityType::GameObject)
	{
		//componentList_.resize(Component::ComponentType::COMPONENT_COUNT, NULL);

#ifdef DEBUG
		cout << "gameobj ctor(str, str): " << id_  << "\t: " << name_ << "(" << tag_ << ")" << endl;
#endif
	}

	GameObject::GameObject(const GameObject& ref)
		:
		name_(ref.name_),
		tag_(ref.tag_),
		id_(_last_id++),
		isActive_(ref.isActive_),
		isArchetype_(ref.isArchetype_),
		mFactoryRef_(ref.mFactoryRef_),
		Entity(EntityType::GameObject)
	{

#ifdef DEBUG
		cout << "gameobj copy ctor: " << id_  << "\t: " << name_ << "(" << tag_ << ")" << endl;
#endif
	}

	bool GameObject::operator==(const GameObject& obj)
	{
		// TODO: Implement==

		return false;
		//return _id == obj._id;
	}

	GameObject::~GameObject()
	{
#ifdef DEBUG
		cout << "gameobj dtor: " << id_ << "\t: " << name_ << "(" << tag_ << ")" << endl;
#endif
		
		/// DEPRECATED
		// NULL pointers are safe to delete, so no need for null checking
		//for (Component* component : componentList_)
		//{
		//	delete component;
		//}
	}

	///////////////////////////////////////////////////////////////////////////////
	// Member functions
	///////////////////////////////////////////////////////////////////////////////

	void GameObject::Update()
	{
		// TODO: Use new handle system to use components

		/// DEPRECATED
		//for (auto& component : componentList_){
		//	if (component) component->Update();
		//}
	}

	//void GameObject::Relay(Message* m)
	//{
	//	for (size_t i = 0; i < Component::ComponentType::COMPONENT_COUNT; i++)
	//	{
	//		if (componentList_[i]) componentList_[i]->HandleMessage(m);
	//	}
	//}

	//void GameObject::RemoveComponent(unsigned i)
	//{
	//	delete componentList_[i];
	//	componentList_[i] = NULL;
	//}

	//void GameObject::Clone(GameObject& obj) const
	//{
	//	assert(isArchetype_);
	//	// check for caller (must be archetype)
	//	if (!isArchetype_)
	//	{
	//		cout << "WARNING: GameObject::Clone() is called by a non-archetype object - caller id: " << id_ << endl;
	//		return;
	//		
	//	}

	//	// if all good, construct the object
	//	else
	//	{
	//		obj.isActive_ = true;
	//		obj.name_ = name_;
	//		obj.tag_ = tag_;
	//		//obj._componentList = _componentList;

	//		for (int i = 0; i < Component::ComponentType::COMPONENT_COUNT; ++i)
	//		{
	//			if (componentList_[i])
	//			{
	//				//typedef CompName _componentList[i]->GetType();
	//				//Component* component = Component::CopyComponent(static_cast<>(_componentList[i]));

	//				Component* component = nullptr;	// don't forget NULL please
	//				switch (componentList_[i]->GetType())
	//				{
	//				case Component::ComponentType::TRANSFORM:
	//					component = new Transform(*static_cast<Transform*>(componentList_[i]));
	//					break;
	//				case Component::ComponentType::PLAYER_CONTROLLER:
	//					component = new PlayerController(*static_cast<PlayerController*>(componentList_[i]));
	//					break;
	//				case Component::ComponentType::SPRITE:	// we might wwanna remove this: sprite = 2D
	//					component = new Sprite(*static_cast<Sprite*>(componentList_[i]));
	//					break;
	//				case Component::ComponentType::MESH:
	//					component = new Mesh(*static_cast<Mesh*>(componentList_[i]));
	//					break;
	//				/*case SELF_DESTRUCT:
	//					component = new SelfDestruct(*static_cast<SelfDestruct*>(componentList_[i]));
	//					break;*/
	//				default:
	//					cout << "WARNING: " << __FUNCTION__ << " Component not in switch statement" << endl;
	//					break;
	//				}	// TODO: THIS NEEDS TO CHANGE. --> implement copy ctors for components...
	//				obj.AddComponent(component);
	//				component->SetOwner(obj.Pntr());
	//			}
	//		}

	//	}
	//}

	/*std::ostream& operator<<(std::ostream& o, const GameObject& obj)
	{
		o << obj.name_ << "(" << obj.id_ << "): pos: " << obj.GetComponent<Transform>()->mTranslation;

		return o;
	}*/