// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	Input.cpp
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/10/19
// Purpose			:	Input system for window, keyboard and mouse event handling
// History			:
// - 2015/10/19		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#include "..\..\Engine.h"

#include <sfml/opengl.hpp>

#include <iostream>

#define DEBUG1


namespace VEngine
{
	Input* Input::_pInstance = NULL;

	Input* Input::Inst()
	{
		if (_pInstance == NULL)	_pInstance = new Input();
		return _pInstance;
	}

	// this is simply a cast from int to keycode (which is an ENUM)
	// keycodes are here: http://www.sfml-dev.org/documentation/2.0/Keyboard_8hpp_source.php
	KeyCode Input::Key(int key)
	{
		return static_cast<KeyCode>(key);
	}

	bool Input::Init()
	{
		// initialize the keyboard state: every key is unpressed (false)
		for (int i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			_prevState.emplace(Key(i), false);
			_currState.emplace(Key(i), false);
		}

		// assign window handle
		_pWindow = Graphics::Inst()->_pWindow;

		// print system info
		std::cout << "Input System Initialized.\n";
		return true;	// always returns true, see calling function VolkEngine::Init()
	}

	void Input::Update()
	{
		//------------------------------------------------
		// EVENT HANDLING
		//------------------------------------------------
		// Events Documentation: http://www.sfml-dev.org/documentation/2.0/classsf_1_1Event.php 
		sf::Event event;

		// Handle some of the relevant window events here in Input Manager
		// such as close, resize, lost/gain focus
		// although key press events exist in SFML, they are not used here and implemented from scratch
		while (_pWindow->pollEvent(event))
		{
			switch (event.type)
			{

				// Close window
			case sf::Event::Closed:
				Engine::Quit();
				break;

				// Resize Window
			case sf::Event::Resized:
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
				GFX->UpdateWindowSize(event.size.width, event.size.height);
				break;

				// focus changes
			case sf::Event::GainedFocus:
				//std::cout << "Gained Focus." << std::endl;
				break;
			case sf::Event::LostFocus:
				//std::cout << "Lost Focus." << std::endl;
				break;
			}
		}

		//------------------------------------------------
		// KEYBOARD STATE
		//------------------------------------------------
		// Update Keyboard state by checking each key individually
		// since SFML doesn't provide a keyboard state.
		// WARNING: Keyboard state is updated EVEN if the game has lost focus
		//			meaning that game will process input when it is alt-tabbed
		for (int i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			_prevState[Key(i)] = _currState[Key(i)];
			_currState[Key(i)] = sf::Keyboard::isKeyPressed(Key(i));
		}

#ifdef DEBUG
		//------------------------------------------------
		// TEST CODE
		//------------------------------------------------
		for (int i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			if (IsKeyTriggered(Key(i))) std::cout << "Triggered: " << Key(i) << std::endl;
			if (IsKeyReleased(Key(i))) std::cout << "Released: " << Key(i) << std::endl;
			if (IsKeyPressed(Key(i))) std::cout << "Pressed: " << Key(i) << std::endl;
		}
#endif

		if (IsKeyTriggered(sf::Keyboard::Key::Escape))	Engine::Quit();
		if (IsKeyTriggered(sf::Keyboard::Key::L))		FrameRateController::Inst()->ToggleFPSLock();
		if (IsKeyTriggered(sf::Keyboard::Key::D))		Engine::ToggleDebug();
		if (IsKeyTriggered(sf::Keyboard::Key::C))		Engine::ToggleCollisionInfo();
		if (IsKeyTriggered(sf::Keyboard::Key::I))		Engine::ToggleInfo();
		if (IsKeyTriggered(sf::Keyboard::Key::F10))		Engine::TogglePause();


	}

	void Input::Cleanup()
	{
		std::cout << "Input System cleaned up.\n";
	}

	//---------------------------------------------------------------
	// Keyboard Functions
	//
	//	cannot use const functions as unordered_map<>[key] will create
	//  a new entry in the container if the value for key doesn't exist
	//	hence, the function is non-const 
	//	refer to: http://stackoverflow.com/questions/13354394/reading-object-from-const-unordered-map
	//---------------------------------------------------------------
	bool Input::IsKeyPressed(const sf::Keyboard::Key key)
	{
		return _currState[key];
	}

	bool Input::IsKeyTriggered(const sf::Keyboard::Key key)
	{
		return !_prevState[key] && _currState[key];
	}

	bool Input::IsKeyReleased(const sf::Keyboard::Key key)
	{
		return _prevState[key] && !_currState[key];
	}
}