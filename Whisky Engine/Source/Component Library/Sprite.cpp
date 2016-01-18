// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	Sprite.cpp
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


#include "Sprite.h"
#include "Graphics.h"
#include <cassert>
#include <algorithm>

using std::vector;
using std::string;

namespace VEngine
{

	
	const ComponentType Sprite::Type = SPRITE;

	void lower(string& s){ std::transform(s.begin(), s.end(), s.begin(), ::tolower); }

	Sprite* Sprite::Deserialize(const char* params)
	{
		vector<string> fileNames = split(params, ' ');
		std::for_each(fileNames.begin(), fileNames.end(), lower);
		return new Sprite(fileNames);
	}

	Sprite::Sprite(const vector<string>& names)
	{
		assert(names.size() > 0);
		for (auto& name : names)
		{
			GLuint* p = Graphics::Inst()->Textures().at(name);
			_sprites.push_back(make_pair(name, p));
		}

		_activeSprite = 0;
	}

	void Sprite::ActivateSprite(unsigned i)
	{
		assert(i < _sprites.size());
		_activeSprite = i;
	}

}