// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	Engine.h
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

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <SFML/System.hpp>

#include "Source/Manager Library/Input.h"
#include "Source/Manager Library/Graphics.h"
#include "Source/Manager Library/GameObjectFactory.h"
#include "Source/Manager Library/FrameRateController.h"
#include "Source/Manager Library/ResourceManager.h"

// handles for Systems/Manager
#define GFX				Graphics::Inst()
#define INP				   Input::Inst()
#define GOM	   GameObjectFactory::Inst()
#define FRC  FrameRateController::Inst()
#define RSC		 ResourceManager::Inst()
#define MSG			   Messaging::Inst()		
#define PHY				 Physics::Inst()

class Engine
{
public:
	Engine(){}

	// Engine Phases
	bool Init();
	bool Load();
	void MainLoop();
	void Unload();
	void Exit();

	void Log() const;

	inline static void Quit()					{ _quit = true; }
	inline static void ToggleDebug()			{ _debug = !_debug; }
	inline static bool IsDebug()				{ return _debug; }
	inline static void ToggleCollisionInfo()	{ _collisionInfo = !_collisionInfo; }
	static void ToggleInfo();

	static const float Version() { return version_; }
	static void TogglePause();
	void RenderPauseMenu();

public:
	// loop flags
	static bool _pause;
	static bool _quit;

	// debug & info flags
	static bool _info;
	static bool _debug;
	static bool _collisionInfo;

	// window info
	static unsigned _resolution_w;
	static unsigned _resolution_h;
private:
	sf::Clock clock_;

	static const float version_;

};
#endif