// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	Input.h
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
#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace VEngine
{
	typedef sf::Keyboard::Key KeyCode;

	class Graphics;

	class Input
	{
	public:
		static Input* Inst();

		bool Init();
		void Update();
		void Cleanup();

		// keyboard input
		static sf::Keyboard::Key Key(int);
		bool IsKeyPressed(const KeyCode);	// 
		bool IsKeyTriggered(const KeyCode);	//	no const, see implementation comments
		bool IsKeyReleased(const KeyCode);	//

		// mouse input

	private:
		// singleton
		Input(){}	// empty ctor/dtor

		static Input* _pInstance;

		// context 
		sf::RenderWindow* _pWindow;

		// keyboard states
		std::unordered_map<KeyCode, bool> _prevState;
		std::unordered_map<KeyCode, bool> _currState;

		// mouse states

	};
}
#endif