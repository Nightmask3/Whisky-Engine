// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	Sprite.h
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/11/15
// Purpose			:	Sprite wrapper component
// History			:
// - 2015/11/15		:	- initial implementation
// - 2015/11/30		:	- multiple sprite functionality added 
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include <glew.h>
#include <SFML/OpenGL.hpp>

class Sprite : public Component
{
public:
	static Sprite* Deserialize(const char*);

	Sprite(const std::vector<std::string>&);

	ComponentType GetType() const { return Type; }

	GLuint* const Texture() const { return _sprites[_activeSprite].second; }
	void ActivateSprite(unsigned);

public:
	static const ComponentType Type;	// formerly used in gameobject template functions

private:
	int _activeSprite;
	std::vector<std::pair<std::string, GLuint*>> _sprites;
};
#endif