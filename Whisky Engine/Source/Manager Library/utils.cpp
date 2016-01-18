// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	utils.cpp
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

#include "utils.h"


using std::vector;
using std::string;

vector<string> split(const char* s, char c)
{
	vector<string> result;

	do
	{
		const char* begin = s;
		while (*s != c && *s) s++;
		result.push_back(string(begin, s));
	} while (*s++);

	return result;
}

vector<string> split(const string& str, char c)
{
	vector<string> result;
	const char* s = str.c_str();
	do
	{
		const char* begin = s;
		while (*s != c && *s) s++;
		result.push_back(string(begin, s));
	} while (*s++);

	return result;
}

float RangeF(float l, float h){
	float n = (float)rand() / RAND_MAX;
	return l + n*(h - l);
}

std::string GetFileNameFromPath(const std::string& path)
{	// example: path: "Archetypes/player.txt" | return val: "player"
	string no_extension = split(path.c_str(), '.')[0];
	auto tokens = split(no_extension.c_str(), '/');
	string name = tokens[tokens.size()-1];
	return name;
}
