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


enum ComponentType{			// update: Components.h | GameObject::Clone() | Component::CreateComponent()
	TRANSFORM,
	MESH,
	SPRITE,

	PLAYER_CONTROLLER,
	SELF_DESTRUCT,

	COMPONENT_COUNT
};

class GameObject;
class Message;
class Component
{
public:
	Component();
	virtual ~Component(){ /*std::cout << "component dtor" << std::endl;*/ }

	virtual void		SetOwner(GameObject* obj)	{ _gameObject = obj; }
	virtual GameObject* GetOwner() const			{ return _gameObject; }
	virtual void		Update(){};
	virtual void		HandleMessage(Message*){}

	virtual ComponentType GetType() const = 0;
	//virtual const std::type_info GetTypeInfo() const = 0;

	static Component* CreateComponent(std::string name, const char* params);

	template <typename ComponentName>
	static ComponentName* CopyComponent(ComponentName*);

protected:
	GameObject* _gameObject;

};

template <typename ComponentName>
ComponentName* Component::CopyComponent(ComponentName* c)
{
	return new ComponentName(c);
}
#endif