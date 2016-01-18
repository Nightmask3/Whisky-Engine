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
#include "glm\vec3.hpp"

class PlayerController : public Component
{
public:
	static PlayerController* Deserialize(const char*);

	PlayerController();
	ComponentType GetType() const { return Type; }

	void Update();
	void HandleMessage(Message*);

	int Hp() const { return _hp; }
	void Hp(int val) { _hp = val; }
	unsigned WeaponCharge() const { return _weaponCharge; }
	void WeaponCharge(unsigned val) { _weaponCharge = val; }
	unsigned WeaponLevel() const { return _weaponLevel; }
	void WeaponLevel(unsigned val) { _weaponLevel = val; }
private:
	void Move();
	void CreateBullet(const glm::vec3& pos);
	void Shoot();
	void CollectPowerUp(GameObject& pUp);
	void AccumulateWeaponCharge(int amount);
	void Hit(GameObject& eBullet, int amount);
public:
	static const ComponentType Type = PLAYER_CONTROLLER;
private:
	float _moveSpeed;
	bool _fire;
	float _fireWhen, _firePeriod;
	unsigned _activeWeapon;	// 0 - 3
	unsigned _weaponLevel;	// 1 - 4
	unsigned _weaponCharge;	// get 10 charges to unlock new weapon lvl
	int _hp;
};

#endif

