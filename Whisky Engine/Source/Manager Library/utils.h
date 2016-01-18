// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	utils.h
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/11/16
// Purpose			:	utility functions
// History			:
// - 2015/11/16		:	- initial implementation: split, 
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#ifndef UTILS_CPP
#define UTILS_CPP

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<std::string> split(const char* s,			char c = ' ');
std::vector<std::string> split(const std::string& s,	char c = ' ');
std::string	GetFileNameFromPath(const std::string&);

float RangeF(float l, float h);

#endif