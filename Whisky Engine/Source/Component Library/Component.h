// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	Component.h
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/10/27
// Purpose			:	Base class for components to be used in game objects
// History			:
// - 2015/10/27		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "..\Manager Library\utils.h"

class GameObject;
class Message;
class Component
{
public:
	enum ComponentType
	{			
		TRANSFORM,
		MESH,
		SPRITE,
		PLAYER_CONTROLLER,
		SELF_DESTRUCT,

		COMPONENT_COUNT
	};
	
	virtual ~Component(){ /*std::cout << "component dtor" << std::endl;*/ }
	virtual void		SetOwner(GameObject* obj)	{ mOwner_ = obj; }
	virtual GameObject* GetOwner() const			{ return  mOwner_; }
	virtual void		Update(){};
	virtual void		HandleMessage(Message*){}
	ComponentType GetType() { return mType; }
	
	ComponentType mType;
	static Component* CreateComponent(std::string name, const char* params);

	template <typename ComponentName>
	static ComponentName* CopyComponent(ComponentName*);

protected:
	GameObject * mOwner_;
	// Made protected because we don't want objects of this class to be instantiated directly, but derived classes can access it
	Component(ComponentType type) : mType(type), mOwner_(nullptr) {}

};

template <typename ComponentName>
ComponentName* Component::CopyComponent(ComponentName* c)
{
	return new ComponentName(c);
}
#endif