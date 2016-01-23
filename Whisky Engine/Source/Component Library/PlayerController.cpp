// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	PlayerController.cpp
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/11/3
// Purpose			:	Component for controlling the player object
// History			:
// - 2015/11/3		:	- initial implementation
// - 2016/1/19		:	- Whiskey Engine integration
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#include <iostream>
#include <SFML\Main.hpp>
#include "PlayerController.h"
#include "..\..\Engine.h"

PlayerController* PlayerController::Deserialize(const char*)
{
	return new PlayerController();
}

void PlayerController::Update()
{
	Move();
}

PlayerController::PlayerController()
	:
	_moveSpeed(15.0f),
	_hp(10),
	Component(ComponentType::PLAYER_CONTROLLER)
{}

void PlayerController::Move()
{
	float frameTime = FRC->FrameDelta();

	if (INP->IsKeyPressed(KeyCode::Up))
		(mOwner_->GetComponent<Transform>())->Translate(glm::vec3(0, 1, 0) * _moveSpeed*frameTime);
		
	if (INP->IsKeyPressed(KeyCode::Down))
		(mOwner_->GetComponent<Transform>())->Translate(glm::vec3(0, -1, 0)* _moveSpeed*frameTime);
		
	if (INP->IsKeyPressed(KeyCode::Left))
		(mOwner_->GetComponent<Transform>())->Translate(glm::vec3(-1, 0, 0)* _moveSpeed*frameTime);
											
	if (INP->IsKeyPressed(KeyCode::Right))
		(mOwner_->GetComponent<Transform>())->Translate(glm::vec3(1, 0, 0)* _moveSpeed*frameTime);	
}

// player collision behavior (physics system will send the collision message)
void PlayerController::HandleMessage(Message* m)
{
	//CollisionMessage* msg = static_cast<CollisionMessage*>(m);
	//if (msg)
	//{
	//	if (msg->Other().Name() == "PowerUp")					CollectPowerUp(msg->Other());
	//	if (msg->Other().Name() == "eBullet")					Hit(msg->Other(), 1);
	//	if (msg->Other().Name().find("Enemy") != string::npos)	Hit(msg->Other(), 3);
	//}
	//else	cout << "ERROR in " << __FUNCTION__ << " : message static cast failed." << endl;
}
