// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	PlayerController.cpp
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/11/3
// Purpose			:	Component for controlling the player object
// History			:
// - 2015/11/3		:	- initial implementation
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
		
	// DEBUG
	if (INP->IsKeyTriggered(KeyCode::Num1)) _weaponLevel = 1;
	if (INP->IsKeyTriggered(KeyCode::Num2)) _weaponLevel = 2;
	if (INP->IsKeyTriggered(KeyCode::Num3)) _weaponLevel = 3;
	if (INP->IsKeyTriggered(KeyCode::Num4)) _weaponLevel = 4;

	if (INP->IsKeyTriggered(KeyCode::Space)) _activeWeapon = (_activeWeapon+1)%_weaponLevel;	// iterate through available weapons

	_fire = INP->IsKeyPressed(KeyCode::LControl);
	if (_fire && FRC->Time() >= _fireWhen)	Shoot();
}



PlayerController::PlayerController()
	:
	_weaponLevel(1),
	_moveSpeed(15.0f),
	_fire(false),
	_fireWhen(0.0f),
	_firePeriod(0.15f),
	_activeWeapon(0),
	_hp(10)
{}

void PlayerController::Move()
{
	float frameTime = FRC->FrameDelta();

	if (INP->IsKeyPressed(KeyCode::Up))
		mOwner_->GetComponent<Transform>()->Translate(0, _moveSpeed*frameTime);
		
	if (INP->IsKeyPressed(KeyCode::Down))
		mOwner_->GetComponent<Transform>()->Translate(0, -_moveSpeed*frameTime);
		
	if (INP->IsKeyPressed(KeyCode::Left))
		mOwner_->GetComponent<Transform>()->Translate(-_moveSpeed*frameTime, 0);
		
	if (INP->IsKeyPressed(KeyCode::Right))
		mOwner_->GetComponent<Transform>()->Translate(_moveSpeed*frameTime, 0);
		
}

//void PlayerController::CreateBullet(const vec3& pos)
//{
//	// hardcoded bullet scales (values are determined using sprite dimensions)
//	float scale_down = 1.0 / 4.0f;
//	glm::vec3 scales[4] =
//	{
//		vec3(3.0f *scale_down, 3.0f*scale_down, 1.0f),
//		vec3(7.0f *scale_down, 9.0f*scale_down, 1.0f),
//		vec3(5.0f *scale_down, 9.0f*scale_down, 1.0f),
//		vec3(10.0f*scale_down, 4.0f*scale_down, 1.0f)
//	};
//
//	int damages[4] = {1, 4, 3, 7};
//
//	// instantiate bullets
//	GameObject& bullet = GOM->InstantiateArchetype("Bullet");
//
//	// set transform
//	bullet.GetComponent<Transform>()->Position(pos);
//	bullet.GetComponent<Transform>()->Scale(scales[_activeWeapon]);
//	bullet.GetComponent<Sprite>()->ActivateSprite(_activeWeapon);
//	bullet.GetComponent<BoxCollider2D>()->Scale(scales[_activeWeapon]/2);
//	bullet.GetComponent<BulletBehavior>()->Damage(damages[_activeWeapon]);
//}

//void PlayerController::Shoot()
//{
//	vec3 ship_pos = mOwner_->GetComponent<Transform>()->Position();
//	vec3 ship_scale = mOwner_->GetComponent<Transform>()->Scale();
//	vec3 pos = vec3(ship_pos[0], ship_pos[1] + ship_scale[1] / 2.0f);	// from the tip of the ship
//
//	if (_activeWeapon == 0 || _activeWeapon == 2)
//	{
//		CreateBullet(vec3(pos[0] + ship_scale[0] / 3, pos[1], pos[2]));	// symmetric shooting
//		CreateBullet(vec3(pos[0] - ship_scale[0] / 3, pos[1], pos[2]));
//	}
//	else	CreateBullet(pos);
//
//
//	_firePeriod = _activeWeapon == 0 ? 0.075f : 0.15f;
//	_fireWhen = FRC->Time() + _firePeriod;	// 0.15f
//}
//
//void PlayerController::CollectPowerUp(GameObject& pUp)
//{
//	switch (pUp.GetComponent<PowerUp>()->PUpType())
//	{
//	case HP:
//		_hp += 2;
//		cout << "Power Up! Hp: " << _hp << endl;
//		break;
//	case WEAPON:
//		AccumulateWeaponCharge(1);	// every weapon up is 1 charge for now
//		break;
//	default:
//		break;
//	}
//	
//	GOM->Destroy(pUp);
//}
//
//void PlayerController::AccumulateWeaponCharge(int amount)
//{
//	const int base = 2;
//	const unsigned nextLevel = base + _weaponLevel-1;
//
//	_weaponCharge += amount;
//	// scale UI too
//	
//	cout << "Current Charge: " << _weaponCharge << "/" << nextLevel << endl;
//
//	// level up!
//	if (_weaponCharge >= nextLevel)
//	{
//		_weaponCharge -= nextLevel;
//		if (_weaponLevel < 4)
//		{
//			_weaponLevel++;
//			_activeWeapon = _weaponLevel - 1;
//		} 
//	}
//}
//
//void PlayerController::Hit(GameObject& eBullet, int amount)
//{
//	_hp -= amount;
//	cout << "HIT! HP: " << _hp << endl;
//	GOM->Destroy(eBullet);
//
//	// GAME OVER
//	if (_hp <= 0){
//		std::pair<bool, GameObject*> result = GOM->Find("HealthBar");
//		if (result.first) result.second->GetComponent<Transform>()->Scale(0, 0);
//		
//		cout << " DEAD! " << endl;
//		GOM->Destroy(*mOwner_);
//	}
//}

// player collision behavior
void PlayerController::HandleMessage(Message* m)
{
	CollisionMessage* msg = static_cast<CollisionMessage*>(m);
	if (msg)
	{
		if (msg->Other().Name() == "PowerUp")					CollectPowerUp(msg->Other());
		if (msg->Other().Name() == "eBullet")					Hit(msg->Other(), 1);
		if (msg->Other().Name().find("Enemy") != string::npos)	Hit(msg->Other(), 3);
	}
	else	cout << "ERROR in " << __FUNCTION__ << " : message static cast failed." << endl;
}
