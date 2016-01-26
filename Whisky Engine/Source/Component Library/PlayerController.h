// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	PlayerController.h
// Author			:	Team Stake
// Creation Date	:	2016/01/17
// Purpose			:	Component for controlling the player object
// History			:
// - 2016/01/17		:	- initial implementation
//
// Copyright(C) 2016 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Component.h"
#include "..\..\Dependencies\glm\glm\vec3.hpp"

class PlayerController : public Component
{
public:
	static PlayerController* Deserialize(const char*);
	static const ComponentType _mType = Component::PLAYER_CONTROLLER;
	PlayerController();

	void Update();
	void HandleMessage(Message*);

	int Hp() const { return _hp; }
	void Hp(int val) { _hp = val; }
private:
	void Move();
private:
	float _moveSpeed;
	int _hp;
};

#endif

