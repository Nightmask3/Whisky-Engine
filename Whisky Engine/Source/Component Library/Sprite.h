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

	GLuint* const Texture() const { return sprites_[activeSprite_].second; }
	void ActivateSprite(unsigned);

private:
	int activeSprite_;
	std::vector<std::pair<std::string, GLuint*>> sprites_;
};
#endif